//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#ifndef ASMITH_OPENGL_COLOUR_HPP
#define ASMITH_OPENGL_COLOUR_HPP

#include "core.hpp"

namespace asmith { namespace gl {

	template<class A, class B>
	static inline A colour_cast(const B& aColour) throw() {
		vec4f tmp;
		aColour.get_rgba(tmp);
		A result;
		result.set_rgba(tmp);
		return result;
	}

	static constexpr int64_t colour_min(const GLenum aType) throw() {
		return
			aType == GL_UNSIGNED_BYTE ? 0 :
			aType == GL_UNSIGNED_SHORT ? 0 :
			aType == GL_UNSIGNED_INT ? 0 :
			aType == GL_BYTE ? INT8_MIN :
			aType == GL_SHORT ? INT16_MIN :
			aType == GL_INT ? INT32_MIN :
			aType == GL_FLOAT ? 0 :
			aType == GL_DOUBLE ? 0 :
			0;
	}

	static constexpr size_t colour_max(const GLenum aType) throw() {
		return
			aType == GL_UNSIGNED_BYTE ? UINT8_MAX :
			aType == GL_UNSIGNED_SHORT ? UINT16_MAX :
			aType == GL_UNSIGNED_INT ? UINT32_MAX :
			aType == GL_BYTE ? INT8_MAX :
			aType == GL_SHORT ? INT16_MAX :
			aType == GL_INT ? INT32_MAX :
			aType == GL_FLOAT ? 1 :
			aType == GL_DOUBLE ? 1 :
			0;
	}
	
	template<const GLenum F, const GLenum T, class ENABLE = void>
	struct colour {
		enum : GLenum {
			FORMAT = F,
			TYPE = T,
			INTERNAL_FORMAT = T,
		};

		enum : int64_t {
			MIN_RED		= 0,
			MIN_GREEN	= 0,
			MIN_BLUE	= 0,
			MIN_ALPHA	= 0,

			MAX_RED		= 0,
			MAX_GREEN	= 0,
			MAX_BLUE	= 0,
			MAX_ALPHA	= 0
		};

		enum {
			RED_CHANNEL		= -1,
			GREEN_CHANNEL	= -1,
			BLUE_CHANNEL	= -1,
			ALPHA_CHANNEL	= -1,

			RED_BITS		= 0,
			GREEN_BITS		= 0,
			BLUEED_BITS		= 0,
			ALPHA_BITS		= 0
		};

		void get_rgba(vec4f&) const throw();
		void set_rgba(const vec4f&) throw();
	};

	template<const GLenum T>
	struct colour<GL_RED, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RED,
			TYPE = T,
			INTERNAL_FORMAT = GL_RED
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= 0,
			MIN_BLUE	= 0,
			MIN_ALPHA	= 0,

			MAX_RED		= colour_max(T),
			MAX_GREEN	= 0,
			MAX_BLUE	= 0,
			MAX_ALPHA	= 0
		};

		enum {
			RED_CHANNEL = 0,
			GREEN_CHANNEL = -1,
			BLUE_CHANNEL = -1,
			ALPHA_CHANNEL = -1,

			RED_BITS = sizeof(type) * 8,
			GREEN_BITS = 0,
			BLUEED_BITS = 0,
			ALPHA_BITS = 0
		};

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = 0.f;
			aValue[2] = 0.f;
			aValue[3] = 1.f;
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
		}

		constexpr colour() :
			r(MIN_RED)
		{}

		constexpr colour(type aR) :
			r(aR)
		{}

		type r;
	};

	template<const GLenum T>
	struct colour<GL_RG, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RG,
			TYPE = T,
			INTERNAL_FORMAT = GL_RG
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= colour_min(T),
			MIN_BLUE	= 0,
			MIN_ALPHA	= 0,

			MAX_RED		= colour_max(T),
			MAX_GREEN	= colour_max(T),
			MAX_BLUE	= 0,
			MAX_ALPHA	= 0
		};

		enum {
			RED_CHANNEL = 0,
			GREEN_CHANNEL = 1,
			BLUE_CHANNEL = -1,
			ALPHA_CHANNEL = -1,

			RED_BITS = sizeof(type) * 8,
			GREEN_BITS = sizeof(type) * 8,
			BLUEED_BITS = 0,
			ALPHA_BITS = 0
		};

		type r;
		type g;

		constexpr colour() :
			r(MIN_RED), g(MIN_GREEN)
		{}

		constexpr colour(type aR, type aG) :
			r(aR), g(aG)
		{}

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = static_cast<GLfloat>(g) / static_cast<GLfloat>(MAX_GREEN);
			aValue[2] = 0.f;
			aValue[3] = 1.f;
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
			g = static_cast<type>(aValue[1] * static_cast<GLfloat>(MAX_GREEN));
		}
	};

	template<const GLenum T>
	struct colour<GL_RGB, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RGB,
			TYPE = T,
			INTERNAL_FORMAT = GL_RGB
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= colour_min(T),
			MIN_BLUE	= colour_min(T),
			MIN_ALPHA	= 0,

			MAX_RED		= colour_max(T),
			MAX_GREEN	= colour_max(T),
			MAX_BLUE	= colour_max(T),
			MAX_ALPHA	= 0
		};

		enum {
			RED_CHANNEL = 0,
			GREEN_CHANNEL = 1,
			BLUE_CHANNEL = 2,
			ALPHA_CHANNEL = -1,

			RED_BITS = sizeof(type) * 8,
			GREEN_BITS = sizeof(type) * 8,
			BLUEED_BITS = sizeof(type) * 8,
			ALPHA_BITS = 0
		};

		type r;
		type g;
		type b;

		constexpr colour() :
			r(MIN_RED), g(MIN_GREEN), b(MIN_BLUE)
		{}

		constexpr colour(type aR, type aG, type aB) :
			r(aR), g(aG), b(aB)
		{}

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = static_cast<GLfloat>(g) / static_cast<GLfloat>(MAX_GREEN);
			aValue[2] = static_cast<GLfloat>(b) / static_cast<GLfloat>(MAX_BLUE);
			aValue[3] = 1.f;
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
			g = static_cast<type>(aValue[1] * static_cast<GLfloat>(MAX_GREEN));
			b = static_cast<type>(aValue[2] * static_cast<GLfloat>(MAX_BLUE));
		}
	};

	template<const GLenum T>
	struct colour<GL_RGBA, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RGBA,
			TYPE = T,
			INTERNAL_FORMAT = GL_RGBA
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= colour_min(T),
			MIN_BLUE	= colour_min(T),
			MIN_ALPHA	= colour_min(T),

			MAX_RED		= colour_max(T),
			MAX_GREEN	= colour_max(T),
			MAX_BLUE	= colour_max(T),
			MAX_ALPHA	= colour_max(T)
		};

		enum {
			RED_CHANNEL = 0,
			GREEN_CHANNEL = 1,
			BLUE_CHANNEL = 2,
			ALPHA_CHANNEL = 3,

			RED_BITS = sizeof(type) * 8,
			GREEN_BITS = sizeof(type) * 8,
			BLUEED_BITS = sizeof(type) * 8,
			ALPHA_BITS = sizeof(type) * 8
		};

		type r;
		type g;
		type b;
		type a;

		constexpr colour() :
			r(MIN_RED), g(MIN_GREEN), b(MIN_BLUE), a(MIN_ALPHA)
		{}

		constexpr colour(type aR, type aG, type aB, type aA) :
			r(aR), g(aG), b(aB), a(aA)
		{}

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = static_cast<GLfloat>(g) / static_cast<GLfloat>(MAX_GREEN);
			aValue[2] = static_cast<GLfloat>(b) / static_cast<GLfloat>(MAX_BLUE);
			aValue[3] = static_cast<GLfloat>(a) / static_cast<GLfloat>(MAX_ALPHA);
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
			g = static_cast<type>(aValue[1] * static_cast<GLfloat>(MAX_GREEN));
			b = static_cast<type>(aValue[2] * static_cast<GLfloat>(MAX_BLUE));
			a = static_cast<type>(aValue[3] * static_cast<GLfloat>(MAX_ALPHA));
		}
	};

	template<const GLenum T>
	struct colour<GL_BGR, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_BGR,
			TYPE = T,
			INTERNAL_FORMAT = GL_RGB
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= colour_min(T),
			MIN_BLUE	= colour_min(T),
			MIN_ALPHA	= 0,

			MAX_RED		= colour_max(T),
			MAX_GREEN	= colour_max(T),
			MAX_BLUE	= colour_max(T),
			MAX_ALPHA	= 0
		};

		enum {
			RED_CHANNEL = 2,
			GREEN_CHANNEL = 1,
			BLUE_CHANNEL = 0,
			ALPHA_CHANNEL = -1,

			RED_BITS = sizeof(type) * 8,
			GREEN_BITS = sizeof(type) * 8,
			BLUEED_BITS = sizeof(type) * 8,
			ALPHA_BITS = 0
		};

		type b;
		type g;
		type r;

		constexpr colour() :
			b(MIN_BLUE), g(MIN_GREEN), r(MIN_RED)
		{}

		constexpr colour(type aB, type aG, type aR) :
			b(aB), g(aG), r(aR)
		{}

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = static_cast<GLfloat>(g) / static_cast<GLfloat>(MAX_GREEN);
			aValue[2] = static_cast<GLfloat>(b) / static_cast<GLfloat>(MAX_BLUE);
			aValue[3] = 1.f;
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
			g = static_cast<type>(aValue[1] * static_cast<GLfloat>(MAX_GREEN));
			b = static_cast<type>(aValue[2] * static_cast<GLfloat>(MAX_BLUE));
		}
	};

	template<const GLenum T>
	struct colour<GL_BGRA, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_BGRA,
			TYPE = T,
			INTERNAL_FORMAT = GL_RGBA
		};

		enum : int64_t {
			MIN_RED		= colour_min(T),
			MIN_GREEN	= colour_min(T),
			MIN_BLUE	= colour_min(T),
			MIN_ALPHA	= colour_min(T),

			MAX_RED		= colour_max(T),
			MAX_GREEN	= colour_max(T),
			MAX_BLUE	= colour_max(T),
			MAX_ALPHA	= colour_max(T)
		};

		enum {
			RED_CHANNEL = 2,
			GREEN_CHANNEL = 1,
			BLUE_CHANNEL = 0,
			ALPHA_CHANNEL = 3,

			RED_BITS		= sizeof(type) * 8,
			GREEN_BITS		= sizeof(type) * 8,
			BLUEED_BITS		= sizeof(type) * 8,
			ALPHA_BITS		= sizeof(type) * 8
		};

		type b;
		type g;
		type r;
		type a;

		constexpr colour() :
			b(MIN_BLUE), g(MIN_GREEN), r(MIN_RED), a(MIN_ALPHA)
		{}

		constexpr colour(type aB, type aG, type aR, type aA) :
			b(aB), g(aG), r(aR), a(aA)
		{}

		void get_rgba(vec4f& aValue) const throw() {
			aValue[0] = static_cast<GLfloat>(r) / static_cast<GLfloat>(MAX_RED);
			aValue[1] = static_cast<GLfloat>(g) / static_cast<GLfloat>(MAX_GREEN);
			aValue[2] = static_cast<GLfloat>(b) / static_cast<GLfloat>(MAX_BLUE);
			aValue[3] = static_cast<GLfloat>(a) / static_cast<GLfloat>(MAX_ALPHA);
		}

		void set_rgba(const vec4f& aValue) throw() {
			r = static_cast<type>(aValue[0] * static_cast<GLfloat>(MAX_RED));
			g = static_cast<type>(aValue[1] * static_cast<GLfloat>(MAX_GREEN));
			b = static_cast<type>(aValue[2] * static_cast<GLfloat>(MAX_BLUE));
			a = static_cast<type>(aValue[3] * static_cast<GLfloat>(MAX_ALPHA));
		}
	};

	// Colour values taken from http://cloford.com/resources/colours/500col.htm

	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIAN_RED(176, 23,	31);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CRIMSON(220, 20, 60);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTPINK(255, 182, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTPINK_1(255, 174, 185);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTPINK_2(238, 162, 173);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTPINK_3(205, 140, 149);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTPINK_4(139, 95, 101);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PINK(255, 192, 203);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PINK_1(255, 181, 197);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PINK_2(238, 169, 184);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PINK_3(205, 145, 158);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PINK_4(139, 99, 108);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALEVIOLET_RED(219, 112, 147);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALEVIOLET_RED_1(255, 130, 171);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALEVIOLET_RED_2(238, 121, 159);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALEVIOLET_RED_3(205, 104, 137);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALEVIOLET_RED_4(139, 71, 93);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAVENDER_BLUSH_1(255, 240, 245);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAVENDER_BLUSH_2(238, 224, 229);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAVENDER_BLUSH_3(205, 193, 197);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAVENDER_BLUSH_4(139, 131, 134);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLET_RED_1(255, 62, 150);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLET_RED_2(238, 58, 140);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLET_RED_3(205, 50, 120);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLET_RED_4(139, 34, 82);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HOTPINK(255, 105, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HOTPINK_1(255, 110, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HOTPINK_2(238, 106, 167);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HOTPINK_3(205, 96, 144);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HOTPINK_4(139, 58, 98);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RASPBERRY(135, 38, 87);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_PINK_1(255, 20, 147);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_PINK_2(238, 18, 137);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_PINK_3(205, 16, 118);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_PINK_4(139, 10, 80);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAROON_1(255, 52, 179);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAROON_2(238, 48, 167);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAROON_3(205, 41, 144);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAROON_4(139, 28, 98);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_VIOLE_TRED(199, 21, 133);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLETRED(208, 32, 144);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORCHID(218, 112, 214);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORCHID_1(255, 131, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORCHID_2(238, 122, 233);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORCHID_3(205, 105, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORCHID_4(139, 71, 137);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> THISTLE(216, 191, 216);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> THISTLE_1(255, 225, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> THISTLE_2(238, 210, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> THISTLE_3(205, 181, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> THISTLE_4(139, 123, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PLUM_1(255, 187, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PLUM_2(238, 174, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PLUM_3(205, 150, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PLUM_4(139, 102, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PLUM(221, 160, 221);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> VIOLET(238, 130, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAGENTA_1(255, 0, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAGENTA_2(238, 0, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAGENTA_3(205, 0, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAGENTA_4(139, 0, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PURPLE(128, 0, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_ORCHID(186, 85, 211);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_ORCHID_1(224, 102, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_ORCHID_2(209, 95, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_ORCHID_3(180, 82, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_ORCHID_4(122, 55, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_VIOLET(148, 0, 211);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORCHID(153, 50, 204);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORCHID_1(191, 62, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORCHID_2(178, 58, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORCHID_3(154, 50, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORCHID_4(104, 34, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIGO(75, 0, 130);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLUE_VIOLET(138, 43, 226);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PURPLE_1(155, 48, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PURPLE_2(145, 44, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PURPLE_3(125, 38, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PURPLE_4(85, 26, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_PURPLE(147, 112, 219);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_PURPLE_1(171, 130, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_PURPLE_2(159, 121, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_PURPLE_3(137, 104, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_PURPLE_4(93, 71, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_BLUE(72, 61, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SLATE_BLUE(132, 112, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_SLATE_BLUE(123, 104, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_BLUE(106, 90, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_BLUE_1(131, 111, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_BLUE_2(122, 103, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_BLUE_3(105, 89, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_BLUE_4(71, 60, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GHOST_WHITE(248, 248, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAVENDER(230, 230, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLUE(0, 0, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLUE_2(0, 0, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLUE_3(0, 0, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLUE_4(0, 0, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> NAVY(0, 0, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MIDNIGHT_BLUE(25, 25, 112);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> COBALT(61, 89, 171);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROYAL_BLUE(65, 105, 225);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROYAL_BLUE_1(72, 118, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROYAL_BLUE_2(67, 110, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROYAL_BLUE_3(58, 95, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROYAL_BLUE_4(39, 64, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORNFLOWER_BLUE(100, 149, 237);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_STEEL_BLUE(176, 196, 222);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_STEEL_BLUE_1(202, 225, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_STEEL_BLUE_2(188, 210, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_STEEL_BLUE_3(162, 181, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_STEEL_BLUE_4(110, 123, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SLATE_GRAY(119, 136, 153);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_GRAY(112, 128, 144);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_GRAY_1(198, 226, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_GRAY_2(185, 211, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_GRAY_3(159, 182, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SLATE_GRAY_4(108, 123, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DODGER_BLUE_1(30, 144, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DODGER_BLUE_2(28, 134, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DODGER_BLUE_3(24, 116, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DODGER_BLUE_4(16, 78, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ALICE_BLUE(240, 248, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> STEEL_BLUE(70, 130, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> STEEL_BLUE_1(99, 184, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> STEEL_BLUE_2(92, 172, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> STEEL_BLUE_3(79, 148, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> STEEL_BLUE_4(54, 100, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SKY_BLUE(135, 206, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SKY_BLUE_1(176, 226, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SKYBLUE_2(164, 211, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SKYBLUE_3(141, 182, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SKYBLUE_4(96, 123, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SKY_BLUE_1(135, 206, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SKY_BLUE_2(126, 192, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SKY_BLUE_3(108, 166, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SKY_BLUE_4(74, 112, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SKY_BLUE(135, 206, 235);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_SKY_BLUE_1(0, 191, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_SKY_BLUE_2(0, 178, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_SKY_BLUE_3(0, 154, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DEEP_SKY_BLUE_4(0, 104, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PEACOCK(51, 161, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_BLUE(173, 216, 230);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_BLUE_1(191, 239, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_BLUE_2(178, 223, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_BLUE_3(154, 192, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_BLUE_4(104, 131, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> POWDER_BLUE(176, 224, 230);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADET_BLUE_1(152, 245, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADET_BLUE_2(142, 229, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADET_BLUE_3(122, 197, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADET_BLUE_4(83, 134, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE_1(0, 245, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE_2(0, 229, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE_3(0, 197, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE_4(0, 134, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADET_BLUE(95, 158, 160);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_TURQUOISE(0, 206, 209);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AZURE_1(240, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AZURE_2(224, 238, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AZURE_3(193, 205, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AZURE_4(131, 139, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_CYAN_1(224, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_CYAN_2(209, 238, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_CYAN_3(180, 205, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_CYAN_4(122, 139, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_TURQUOISE_1(187, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_TURQUOISE_2(174, 238, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_TURQUOISE_3(150, 205, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_TURQUOISE_4(102, 139, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_GRAY(47, 79, 79);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_GRAY_1(151, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_GRAY_2(141, 238, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_GRAY_3(121, 205, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SLATE_GRAY_4(82, 139, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CYAN_1(0, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CYAN_2(0, 238, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CYAN_3(0, 205, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CYAN_4(0, 139, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TEAL(0, 128, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_TURQUOISE(72, 209, 204);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SEA_GREEN(32, 178, 170);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MANGANESE_BLUE(3, 168, 158);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE(64, 224, 208);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> COLD_GREY(128, 138, 135);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TURQUOISE_BLUE(0, 199, 140);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AQUAMARINE_1(127, 255, 212);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AQUAMARINE_2(118, 238, 198);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AQUAMARINE_3(102, 205, 170);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> AQUAMARINE_4(69, 139, 116);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_SPRING_GREEN(0, 250, 154);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MINT_CREAM(245, 255, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SPRING_GREEN(0, 255, 127);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SPRING_GREEN_1(0, 238, 118);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SPRING_GREEN_2(0, 205, 102);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SPRING_GREEN_3(0, 139, 69);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MEDIUM_SEA_GREEN(60, 179, 113);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEA_GREEN_1(84, 255, 159);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEA_GREEN_2(78, 238, 148);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEA_GREEN_3(67, 205, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEA_GREEN_4(46, 139, 87);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> EMERALD_GREEN(0, 201, 87);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MINT(189, 252, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> COBALT_GREEN(61, 145, 64);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HONEYDEW_1(240, 255, 240);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HONEYDEW_2(224, 238, 224);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HONEYDEW_3(193, 205, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> HONEYDEW_4(131, 139, 131);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SEA_GREEN(143, 188, 143);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SEA_GREEN_1(193, 255, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SEA_GREEN_2(180, 238, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SEA_GREEN_3(155, 205, 155);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SEA_GREEN_4(105, 139, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GREEN(152, 251, 152);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GREEN_1(154, 255, 154);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GREEN_2(144, 238, 144);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GREEN_3(124, 205, 124);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GREEN_4(84, 139, 84);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIME_GREEN(50, 205, 50);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FOREST_GREEN(34, 139, 34);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN_1(0, 255, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN_2(0, 238, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN_3(0, 205, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN_4(0, 139, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN(0, 128, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_GREEN(0, 100, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SAP_GREEN(48, 128, 20);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LAWN_GREEN(124, 252, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHARTREUSE_1(127, 255, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHARTREUSE_2(118, 238, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHARTREUSE_3(102, 205, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHARTREUSE_4(69, 139, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GREEN_YELLOW(173, 255, 47);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_OLIVE_GREEN_1(202, 255, 112);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_OLIVE_GREEN_2(188, 238, 104);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_OLIVE_GREEN_3(162, 205, 90);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_OLIVE_GREEN_4(110, 139, 61);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_OLIVE_GREEN(85, 107, 47);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE_DRAB(107, 142, 35);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE_DRAB_1(192, 255, 62);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE_DRAB_2(179, 238, 58);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE_DRAB_3(154, 205, 50);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE_DRAB_4(105, 139, 34);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> IVORY_1(255, 255, 240);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> IVORY_2(238, 238, 224);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> IVORY_3(205, 205, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> IVORY_4(139, 139, 131);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BEIGE(245, 245, 220);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_YELLOW_1(255, 255, 224);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_YELLOW_2(238, 238, 209);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_YELLOW_3(205, 205, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_YELLOW_4(139, 139, 122);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GOLDENROD_YELLOW(250, 250, 210);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> YELLOW_1(255, 255, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> YELLOW_2(238, 238, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> YELLOW_3(205, 205, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> YELLOW_4(139, 139, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WARM_GREY(128, 128, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLIVE(128, 128, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_KHAKI(189, 183, 107);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> KHAKI_1(255, 246, 143);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> KHAKI_2(238, 230, 133);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> KHAKI_3(205, 198, 115);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> KHAKI_4(139, 134, 78);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> KHAKI(240, 230, 140);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PALE_GOLDENROD(238, 232, 170);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LEMON_CHIFFON_1(255, 250, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LEMON_CHIFFON_2(238, 233, 191);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LEMON_CHIFFON_3(205, 201, 165);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LEMON_CHIFFON_4(139, 137, 112);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GOLDENROD_1(255, 236, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GOLDENROD_2(238, 220, 130);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GOLDENROD_3(205, 190, 112);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GOLDENROD_4(139, 129, 76);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BANANA(227, 207, 87);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLD_1(255, 215, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLD_2(238, 201, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLD_3(205, 173, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLD_4(139, 117, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORNSILK_1(255, 248, 220);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORNSILK_2(238, 232, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORNSILK_3(205, 200, 177);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORNSILK_4(139, 136, 120);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLDENROD(218, 165, 32);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLDENROD_1(255, 193, 37);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLDENROD_2(238, 180, 34);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLDENROD_3(205, 155, 29);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GOLDENROD_4(139, 105, 20);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARKGOLDENROD(184, 134, 11);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARKGOLDENROD_1(255, 185, 15);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARKGOLDENROD_2(238, 173, 14);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARKGOLDENROD_3(205, 149, 12);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARKGOLDENROD_4(139, 101, 8);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_1(255, 165, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_2(238, 154, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_3(205, 133, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_4(139, 90, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FLORAL_WHITE(255, 250, 240);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> OLD_LACE(253, 245, 230);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHEAT(245, 222, 179);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHEAT_1(255, 231, 186);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHEAT_2(238, 216, 174);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHEAT_3(205, 186, 150);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHEAT_4(139, 126, 102);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MOCCASIN(255, 228, 181);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PAPAYA_WHIP(255, 239, 213);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLANCHED_ALMOND(255, 235, 205);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> NAVAJO_WHITE_1(255, 222, 173);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> NAVAJO_WHITE_2(238, 207, 161);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> NAVAJO_WHITE_3(205, 179, 139);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> NAVAJO_WHITE_4(139, 121, 94);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> EGGSHELL(252, 230, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TAN(210, 180, 140);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BRICK(156, 102, 31);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADMIUM_YELLOW(255, 153, 18);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ANTIQUE_WHITE(250, 235, 215);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ANTIQUE_WHITE_1(255, 239, 219);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ANTIQUE_WHITE_2(238, 223, 204);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ANTIQUE_WHITE_3(205, 192, 176);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ANTIQUE_WHITE_4(139, 131, 120);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURLYWOOD(222, 184, 135);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURLYWOOD_1(255, 211, 155);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURLYWOOD_2(238, 197, 145);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURLYWOOD_3(205, 170, 125);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURLYWOOD_4(139, 115, 85);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BISQUE_1(255, 228, 196);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BISQUE_2(238, 213, 183);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BISQUE_3(205, 183, 158);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BISQUE_4(139, 125, 107);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MELON(227, 168, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CARROT(237, 145, 33);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORANGE(255, 140, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORANGE_1(255, 127, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORANGE_2(238, 118, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORANGE_3(205, 102, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_ORANGE_4(139, 69, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE(255, 128, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TAN_1(255, 165, 79);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TAN_2(238, 154, 73);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TAN_3(205, 133, 63);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TAN_4(139, 90, 43);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LINEN(250, 240, 230);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PEACHPUFF_1(255, 218, 185);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PEACHPUFF_2(238, 203, 173);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PEACHPUFF_3(205, 175, 149);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> PEACHPUFF_4(139, 119, 101);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEASHELL_1(255, 245, 238);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEASHELL_2(238, 229, 222);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEASHELL_3(205, 197, 191);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEASHELL_4(139, 134, 130);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SANDY_BROWN(244, 164, 96);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RAW_SIENNA(199, 97, 20);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHOCOLATE(210, 105, 30);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHOCOLATE_1(255, 127, 36);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHOCOLATE_2(238, 118, 33);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHOCOLATE_3(205, 102, 29);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CHOCOLATE_4(139, 69, 19);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> IVORY_BLACK(41, 36, 33);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FLESH(255, 125, 64);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CADMIUM_ORANGE(255, 97, 3);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURNT_SIENNA(138, 54, 15);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SIENNA(160, 82, 45);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SIENNA_1(255, 130, 71);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SIENNA_2(238, 121, 66);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SIENNA_3(205, 104, 57);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SIENNA_4(139, 71, 38);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SALMON_1(255, 160, 122);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SALMON_2(238, 149, 114);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SALMON_3(205, 129, 98);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_SALMON_4(139, 87, 66);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORAL(255, 127, 80);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_RED_1(255, 69, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_RED_2(238, 64, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_RED_3(205, 55, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ORANGE_RED_4(139, 37, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SEPIA(94, 38, 18);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_SALMON(233, 150, 122);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SALMON_1(255, 140, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SALMON_2(238, 130, 98);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SALMON_3(205, 112, 84);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SALMON_4(139, 76, 57);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORAL_1(255, 114, 86);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORAL_2(238, 106, 80);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORAL_3(205, 91, 69);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> CORAL_4(139, 62, 47);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BURNTUMBER(138, 51, 36);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TOMATO_1(255, 99, 71);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TOMATO_2(238, 92, 66);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TOMATO_3(205, 79, 57);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> TOMATO_4(139, 54, 38);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SALMON(250, 128, 114);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MISTY_ROSE_1(255, 228, 225);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MISTY_ROSE_2(238, 213, 210);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MISTY_ROSE_3(205, 183, 181);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MISTY_ROSE_4(139, 125, 123);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SNOW_1(255, 250, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SNOW_2(238, 233, 233);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SNOW_3(205, 201, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SNOW_4(139, 137, 137);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROSY_BROWN(188, 143, 143);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROSY_BROWN_1(255, 193, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROSY_BROWN_2(238, 180, 180);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROSY_BROWN_3(205, 155, 155);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> ROSY_BROWN_4(139, 105, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHTCORAL(240, 128, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIANRED(205, 92, 92);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIANRED_1(255, 106, 106);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIANRED_2(238, 99, 99);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIANRED_4(139, 58, 58);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> INDIANRED_3(205, 85, 85);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BROWN(165, 42, 42);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BROWN_1(255, 64, 64);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BROWN_2(238, 59, 59);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BROWN_3(205, 51, 51);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BROWN_4(139, 35, 35);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FIRE_BRICK(178, 34, 34);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FIRE_BRICK_1(255, 48, 48);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FIRE_BRICK_2(238, 44, 44);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FIRE_BRICK_3(205, 38, 38);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> FIRE_BRICK_4(139, 26, 26);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RED_1(255, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RED_2(238, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RED_3(205, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> RED_4(139, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> MAROON(128, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_BEET(142, 56, 142);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_SLATEBLUE(113, 113, 198);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_LIGHTBLUE(125, 158, 192);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_TEAL(56, 142, 142);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_CHARTREUSE(113, 198, 113);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_OLIVEDRAB(142, 142, 56);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_BRIGHTGRAY(197, 193, 170);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_SALMON(198, 113, 113);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_DARKGRAY(85, 85, 85);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_12(30, 30, 30);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_16(40, 40, 40);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_32(81, 81, 81);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_36(91, 91, 91);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_52(132, 132, 132);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_56(142, 142, 142);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_LIGHTGRAY(170, 170, 170);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_72(183, 183, 183);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_76(193, 193, 193);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_92(234, 234, 234);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SGI_GRAY_96(244, 244, 244);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHITE(255, 255, 255);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> WHITE_SMOKE(245, 245, 245);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GAINSBORO(220, 220, 220);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> LIGHT_GREY(211, 211, 211);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> SILVER(192, 192, 192);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DARK_GRAY(169, 169, 169);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY(128, 128, 128);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> DIM_GRAY(105, 105, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> BLACK(0, 0, 0);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_99(252, 252, 252);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_98(250, 250, 250);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_97(247, 247, 247);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_96(245, 245, 245);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_95(242, 242, 242);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_94(240, 240, 240);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_93(237, 237, 237);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_92(235, 235, 235);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_91(232, 232, 232);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_90(229, 229, 229);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_89(227, 227, 227);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_88(224, 224, 224);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_87(222, 222, 222);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_86(219, 219, 219);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_85(217, 217, 217);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_84(214, 214, 214);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_83(212, 212, 212);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_82(209, 209, 209);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_81(207, 207, 207);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_80(204, 204, 204);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_79(201, 201, 201);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_78(199, 199, 199);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_77(196, 196, 196);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_76(194, 194, 194);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_75(191, 191, 191);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_74(189, 189, 189);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_73(186, 186, 186);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_72(184, 184, 184);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_71(181, 181, 181);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_70(179, 179, 179);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_69(176, 176, 176);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_68(173, 173, 173);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_67(171, 171, 171);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_66(168, 168, 168);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_65(166, 166, 166);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_64(163, 163, 163);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_63(161, 161, 161);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_62(158, 158, 158);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_61(156, 156, 156);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_60(153, 153, 153);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_59(150, 150, 150);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_58(148, 148, 148);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_57(145, 145, 145);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_56(143, 143, 143);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_55(140, 140, 140);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_54(138, 138, 138);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_53(135, 135, 135);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_52(133, 133, 133);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_51(130, 130, 130);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_50(127, 127, 127);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_49(125, 125, 125);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_48(122, 122, 122);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_47(120, 120, 120);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_46(117, 117, 117);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_45(115, 115, 115);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_44(112, 112, 112);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_43(110, 110, 110);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_42(107, 107, 107);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_41(105, 105, 105);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_40(102, 102, 102);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_39(99, 99, 99);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_38(97, 97, 97);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_37(94, 94, 94);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_36(92, 92, 92);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_35(89, 89, 89);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_34(87, 87, 87);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_33(84, 84, 84);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_32(82, 82, 82);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_31(79, 79, 79);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_30(77, 77, 77);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_29(74, 74, 74);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_28(71, 71, 71);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_27(69, 69, 69);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_26(66, 66, 66);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_25(64, 64, 64);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_24(61, 61, 61);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_23(59, 59, 59);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_22(56, 56, 56);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_21(54, 54, 54);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_20(51, 51, 51);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_19(48, 48, 48);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_18(46, 46, 46);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_17(43, 43, 43);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_16(41, 41, 41);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_15(38, 38, 38);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_14(36, 36, 36);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_13(33, 33, 33);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_12(31, 31, 31);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_11(28, 28, 28);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_10(26, 26, 26);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_9(23, 23, 23);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_8(20, 20, 20);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_7(18, 18, 18);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_6(15, 15, 15);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_5(13, 13, 13);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_4(10, 10, 10);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_3(8, 8, 8);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_2(5, 5, 5);
	static constexpr colour<GL_RGB, GL_UNSIGNED_BYTE> GRAY_1(3, 3, 3);
}}

#endif