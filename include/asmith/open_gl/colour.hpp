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

	template<const GLenum T> using colour_r = colour<GL_RED, T>;
	template<const GLenum T> using colour_rg = colour<GL_RG, T>;
	template<const GLenum T> using colour_rgb = colour<GL_RGB, T>;
	template<const GLenum T> using colour_rgba = colour<GL_RGBA, T>;
	template<const GLenum T> using colour_bgr = colour<GL_BGR, T>;
	template<const GLenum T> using colour_bgra = colour<GL_BGRA, T>;

	typedef colour_r<GL_UNSIGNED_BYTE> colour_r_8u;
	typedef colour_rg<GL_UNSIGNED_BYTE> colour_rg_8u;
	typedef colour_rgb<GL_UNSIGNED_BYTE> colour_rgb_8u;
	typedef colour_rgba<GL_UNSIGNED_BYTE> colour_rgba_8u;
	typedef colour_bgr<GL_UNSIGNED_BYTE> colour_bgr_8u;
	typedef colour_bgra<GL_UNSIGNED_BYTE> colour_bgra_8u;

	typedef colour_r<GL_BYTE> colour_r_8i;
	typedef colour_rg<GL_BYTE> colour_rg_8i;
	typedef colour_rgb<GL_BYTE> colour_rgb_8i;
	typedef colour_rgba<GL_BYTE> colour_rgba_8i;
	typedef colour_bgr<GL_BYTE> colour_bgr_8i;
	typedef colour_bgra<GL_BYTE> colour_bgra_8i;

	typedef colour_r<GL_FLOAT> colour_r_f;
	typedef colour_rg<GL_FLOAT> colour_rg_f;
	typedef colour_rgb<GL_FLOAT> colour_rgb_f;
	typedef colour_rgba<GL_FLOAT> colour_rgba_f;
	typedef colour_bgr<GL_FLOAT> colour_bgr_f;
	typedef colour_bgra<GL_FLOAT> colour_bgra_f;

	// Colour values taken from http://cloford.com/resources/colours/500col.htm

	static constexpr const colour_rgb_8u INDIAN_RED(176, 23, 31);
	static constexpr const colour_rgb_8u CRIMSON(220, 20, 60);
	static constexpr const colour_rgb_8u LIGHT_PINK(255, 182, 193);
	static constexpr const colour_rgb_8u LIGHT_PINK_1(255, 174, 185);
	static constexpr const colour_rgb_8u LIGHT_PINK_2(238, 162, 173);
	static constexpr const colour_rgb_8u LIGHT_PINK_3(205, 140, 149);
	static constexpr const colour_rgb_8u LIGHT_PINK_4(139, 95, 101);
	static constexpr const colour_rgb_8u PINK(255, 192, 203);
	static constexpr const colour_rgb_8u PINK_1(255, 181, 197);
	static constexpr const colour_rgb_8u PINK_2(238, 169, 184);
	static constexpr const colour_rgb_8u PINK_3(205, 145, 158);
	static constexpr const colour_rgb_8u PINK_4(139, 99, 108);
	static constexpr const colour_rgb_8u PALE_VIOLET_RED(219, 112, 147);
	static constexpr const colour_rgb_8u PALE_VIOLET_RED_1(255, 130, 171);
	static constexpr const colour_rgb_8u PALE_VIOLET_RED_2(238, 121, 159);
	static constexpr const colour_rgb_8u PALE_VIOLET_RED_3(205, 104, 137);
	static constexpr const colour_rgb_8u PALE_VIOLET_RED_4(139, 71, 93);
	static constexpr const colour_rgb_8u LAVENDER_BLUSH_1(255, 240, 245);
	static constexpr const colour_rgb_8u LAVENDER_BLUSH_2(238, 224, 229);
	static constexpr const colour_rgb_8u LAVENDER_BLUSH_3(205, 193, 197);
	static constexpr const colour_rgb_8u LAVENDER_BLUSH_4(139, 131, 134);
	static constexpr const colour_rgb_8u VIOLET_RED_1(255, 62, 150);
	static constexpr const colour_rgb_8u VIOLET_RED_2(238, 58, 140);
	static constexpr const colour_rgb_8u VIOLET_RED_3(205, 50, 120);
	static constexpr const colour_rgb_8u VIOLET_RED_4(139, 34, 82);
	static constexpr const colour_rgb_8u HOTPINK(255, 105, 180);
	static constexpr const colour_rgb_8u HOTPINK_1(255, 110, 180);
	static constexpr const colour_rgb_8u HOTPINK_2(238, 106, 167);
	static constexpr const colour_rgb_8u HOTPINK_3(205, 96, 144);
	static constexpr const colour_rgb_8u HOTPINK_4(139, 58, 98);
	static constexpr const colour_rgb_8u RASPBERRY(135, 38, 87);
	static constexpr const colour_rgb_8u DEEP_PINK_1(255, 20, 147);
	static constexpr const colour_rgb_8u DEEP_PINK_2(238, 18, 137);
	static constexpr const colour_rgb_8u DEEP_PINK_3(205, 16, 118);
	static constexpr const colour_rgb_8u DEEP_PINK_4(139, 10, 80);
	static constexpr const colour_rgb_8u MAROON_1(255, 52, 179);
	static constexpr const colour_rgb_8u MAROON_2(238, 48, 167);
	static constexpr const colour_rgb_8u MAROON_3(205, 41, 144);
	static constexpr const colour_rgb_8u MAROON_4(139, 28, 98);
	static constexpr const colour_rgb_8u MEDIUM_VIOLE_TRED(199, 21, 133);
	static constexpr const colour_rgb_8u VIOLETRED(208, 32, 144);
	static constexpr const colour_rgb_8u ORCHID(218, 112, 214);
	static constexpr const colour_rgb_8u ORCHID_1(255, 131, 250);
	static constexpr const colour_rgb_8u ORCHID_2(238, 122, 233);
	static constexpr const colour_rgb_8u ORCHID_3(205, 105, 201);
	static constexpr const colour_rgb_8u ORCHID_4(139, 71, 137);
	static constexpr const colour_rgb_8u THISTLE(216, 191, 216);
	static constexpr const colour_rgb_8u THISTLE_1(255, 225, 255);
	static constexpr const colour_rgb_8u THISTLE_2(238, 210, 238);
	static constexpr const colour_rgb_8u THISTLE_3(205, 181, 205);
	static constexpr const colour_rgb_8u THISTLE_4(139, 123, 139);
	static constexpr const colour_rgb_8u PLUM_1(255, 187, 255);
	static constexpr const colour_rgb_8u PLUM_2(238, 174, 238);
	static constexpr const colour_rgb_8u PLUM_3(205, 150, 205);
	static constexpr const colour_rgb_8u PLUM_4(139, 102, 139);
	static constexpr const colour_rgb_8u PLUM(221, 160, 221);
	static constexpr const colour_rgb_8u VIOLET(238, 130, 238);
	static constexpr const colour_rgb_8u MAGENTA_1(255, 0, 255);
	static constexpr const colour_rgb_8u MAGENTA_2(238, 0, 238);
	static constexpr const colour_rgb_8u MAGENTA_3(205, 0, 205);
	static constexpr const colour_rgb_8u MAGENTA_4(139, 0, 139);
	static constexpr const colour_rgb_8u PURPLE(128, 0, 128);
	static constexpr const colour_rgb_8u MEDIUM_ORCHID(186, 85, 211);
	static constexpr const colour_rgb_8u MEDIUM_ORCHID_1(224, 102, 255);
	static constexpr const colour_rgb_8u MEDIUM_ORCHID_2(209, 95, 238);
	static constexpr const colour_rgb_8u MEDIUM_ORCHID_3(180, 82, 205);
	static constexpr const colour_rgb_8u MEDIUM_ORCHID_4(122, 55, 139);
	static constexpr const colour_rgb_8u DARK_VIOLET(148, 0, 211);
	static constexpr const colour_rgb_8u DARK_ORCHID(153, 50, 204);
	static constexpr const colour_rgb_8u DARK_ORCHID_1(191, 62, 255);
	static constexpr const colour_rgb_8u DARK_ORCHID_2(178, 58, 238);
	static constexpr const colour_rgb_8u DARK_ORCHID_3(154, 50, 205);
	static constexpr const colour_rgb_8u DARK_ORCHID_4(104, 34, 139);
	static constexpr const colour_rgb_8u INDIGO(75, 0, 130);
	static constexpr const colour_rgb_8u BLUE_VIOLET(138, 43, 226);
	static constexpr const colour_rgb_8u PURPLE_1(155, 48, 255);
	static constexpr const colour_rgb_8u PURPLE_2(145, 44, 238);
	static constexpr const colour_rgb_8u PURPLE_3(125, 38, 205);
	static constexpr const colour_rgb_8u PURPLE_4(85, 26, 139);
	static constexpr const colour_rgb_8u MEDIUM_PURPLE(147, 112, 219);
	static constexpr const colour_rgb_8u MEDIUM_PURPLE_1(171, 130, 255);
	static constexpr const colour_rgb_8u MEDIUM_PURPLE_2(159, 121, 238);
	static constexpr const colour_rgb_8u MEDIUM_PURPLE_3(137, 104, 205);
	static constexpr const colour_rgb_8u MEDIUM_PURPLE_4(93, 71, 139);
	static constexpr const colour_rgb_8u DARK_SLATE_BLUE(72, 61, 139);
	static constexpr const colour_rgb_8u LIGHT_SLATE_BLUE(132, 112, 255);
	static constexpr const colour_rgb_8u MEDIUM_SLATE_BLUE(123, 104, 238);
	static constexpr const colour_rgb_8u SLATE_BLUE(106, 90, 205);
	static constexpr const colour_rgb_8u SLATE_BLUE_1(131, 111, 255);
	static constexpr const colour_rgb_8u SLATE_BLUE_2(122, 103, 238);
	static constexpr const colour_rgb_8u SLATE_BLUE_3(105, 89, 205);
	static constexpr const colour_rgb_8u SLATE_BLUE_4(71, 60, 139);
	static constexpr const colour_rgb_8u GHOST_WHITE(248, 248, 255);
	static constexpr const colour_rgb_8u LAVENDER(230, 230, 250);
	static constexpr const colour_rgb_8u BLUE(0, 0, 255);
	static constexpr const colour_rgb_8u BLUE_2(0, 0, 238);
	static constexpr const colour_rgb_8u BLUE_3(0, 0, 205);
	static constexpr const colour_rgb_8u BLUE_4(0, 0, 139);
	static constexpr const colour_rgb_8u NAVY(0, 0, 128);
	static constexpr const colour_rgb_8u MIDNIGHT_BLUE(25, 25, 112);
	static constexpr const colour_rgb_8u COBALT(61, 89, 171);
	static constexpr const colour_rgb_8u ROYAL_BLUE(65, 105, 225);
	static constexpr const colour_rgb_8u ROYAL_BLUE_1(72, 118, 255);
	static constexpr const colour_rgb_8u ROYAL_BLUE_2(67, 110, 238);
	static constexpr const colour_rgb_8u ROYAL_BLUE_3(58, 95, 205);
	static constexpr const colour_rgb_8u ROYAL_BLUE_4(39, 64, 139);
	static constexpr const colour_rgb_8u CORNFLOWER_BLUE(100, 149, 237);
	static constexpr const colour_rgb_8u LIGHT_STEEL_BLUE(176, 196, 222);
	static constexpr const colour_rgb_8u LIGHT_STEEL_BLUE_1(202, 225, 255);
	static constexpr const colour_rgb_8u LIGHT_STEEL_BLUE_2(188, 210, 238);
	static constexpr const colour_rgb_8u LIGHT_STEEL_BLUE_3(162, 181, 205);
	static constexpr const colour_rgb_8u LIGHT_STEEL_BLUE_4(110, 123, 139);
	static constexpr const colour_rgb_8u LIGHT_SLATE_GRAY(119, 136, 153);
	static constexpr const colour_rgb_8u SLATE_GRAY(112, 128, 144);
	static constexpr const colour_rgb_8u SLATE_GRAY_1(198, 226, 255);
	static constexpr const colour_rgb_8u SLATE_GRAY_2(185, 211, 238);
	static constexpr const colour_rgb_8u SLATE_GRAY_3(159, 182, 205);
	static constexpr const colour_rgb_8u SLATE_GRAY_4(108, 123, 139);
	static constexpr const colour_rgb_8u DODGER_BLUE_1(30, 144, 255);
	static constexpr const colour_rgb_8u DODGER_BLUE_2(28, 134, 238);
	static constexpr const colour_rgb_8u DODGER_BLUE_3(24, 116, 205);
	static constexpr const colour_rgb_8u DODGER_BLUE_4(16, 78, 139);
	static constexpr const colour_rgb_8u ALICE_BLUE(240, 248, 255);
	static constexpr const colour_rgb_8u STEEL_BLUE(70, 130, 180);
	static constexpr const colour_rgb_8u STEEL_BLUE_1(99, 184, 255);
	static constexpr const colour_rgb_8u STEEL_BLUE_2(92, 172, 238);
	static constexpr const colour_rgb_8u STEEL_BLUE_3(79, 148, 205);
	static constexpr const colour_rgb_8u STEEL_BLUE_4(54, 100, 139);
	static constexpr const colour_rgb_8u LIGHT_SKY_BLUE(135, 206, 250);
	static constexpr const colour_rgb_8u LIGHT_SKY_BLUE_1(176, 226, 255);
	static constexpr const colour_rgb_8u LIGHT_SKYBLUE_2(164, 211, 238);
	static constexpr const colour_rgb_8u LIGHT_SKYBLUE_3(141, 182, 205);
	static constexpr const colour_rgb_8u LIGHT_SKYBLUE_4(96, 123, 139);
	static constexpr const colour_rgb_8u SKY_BLUE_1(135, 206, 255);
	static constexpr const colour_rgb_8u SKY_BLUE_2(126, 192, 238);
	static constexpr const colour_rgb_8u SKY_BLUE_3(108, 166, 205);
	static constexpr const colour_rgb_8u SKY_BLUE_4(74, 112, 139);
	static constexpr const colour_rgb_8u SKY_BLUE(135, 206, 235);
	static constexpr const colour_rgb_8u DEEP_SKY_BLUE_1(0, 191, 255);
	static constexpr const colour_rgb_8u DEEP_SKY_BLUE_2(0, 178, 238);
	static constexpr const colour_rgb_8u DEEP_SKY_BLUE_3(0, 154, 205);
	static constexpr const colour_rgb_8u DEEP_SKY_BLUE_4(0, 104, 139);
	static constexpr const colour_rgb_8u PEACOCK(51, 161, 201);
	static constexpr const colour_rgb_8u LIGHT_BLUE(173, 216, 230);
	static constexpr const colour_rgb_8u LIGHT_BLUE_1(191, 239, 255);
	static constexpr const colour_rgb_8u LIGHT_BLUE_2(178, 223, 238);
	static constexpr const colour_rgb_8u LIGHT_BLUE_3(154, 192, 205);
	static constexpr const colour_rgb_8u LIGHT_BLUE_4(104, 131, 139);
	static constexpr const colour_rgb_8u POWDER_BLUE(176, 224, 230);
	static constexpr const colour_rgb_8u CADET_BLUE_1(152, 245, 255);
	static constexpr const colour_rgb_8u CADET_BLUE_2(142, 229, 238);
	static constexpr const colour_rgb_8u CADET_BLUE_3(122, 197, 205);
	static constexpr const colour_rgb_8u CADET_BLUE_4(83, 134, 139);
	static constexpr const colour_rgb_8u TURQUOISE_1(0, 245, 255);
	static constexpr const colour_rgb_8u TURQUOISE_2(0, 229, 238);
	static constexpr const colour_rgb_8u TURQUOISE_3(0, 197, 205);
	static constexpr const colour_rgb_8u TURQUOISE_4(0, 134, 139);
	static constexpr const colour_rgb_8u CADET_BLUE(95, 158, 160);
	static constexpr const colour_rgb_8u DARK_TURQUOISE(0, 206, 209);
	static constexpr const colour_rgb_8u AZURE_1(240, 255, 255);
	static constexpr const colour_rgb_8u AZURE_2(224, 238, 238);
	static constexpr const colour_rgb_8u AZURE_3(193, 205, 205);
	static constexpr const colour_rgb_8u AZURE_4(131, 139, 139);
	static constexpr const colour_rgb_8u LIGHT_CYAN_1(224, 255, 255);
	static constexpr const colour_rgb_8u LIGHT_CYAN_2(209, 238, 238);
	static constexpr const colour_rgb_8u LIGHT_CYAN_3(180, 205, 205);
	static constexpr const colour_rgb_8u LIGHT_CYAN_4(122, 139, 139);
	static constexpr const colour_rgb_8u PALE_TURQUOISE_1(187, 255, 255);
	static constexpr const colour_rgb_8u PALE_TURQUOISE_2(174, 238, 238);
	static constexpr const colour_rgb_8u PALE_TURQUOISE_3(150, 205, 205);
	static constexpr const colour_rgb_8u PALE_TURQUOISE_4(102, 139, 139);
	static constexpr const colour_rgb_8u DARK_SLATE_GRAY(47, 79, 79);
	static constexpr const colour_rgb_8u DARK_SLATE_GRAY_1(151, 255, 255);
	static constexpr const colour_rgb_8u DARK_SLATE_GRAY_2(141, 238, 238);
	static constexpr const colour_rgb_8u DARK_SLATE_GRAY_3(121, 205, 205);
	static constexpr const colour_rgb_8u DARK_SLATE_GRAY_4(82, 139, 139);
	static constexpr const colour_rgb_8u CYAN_1(0, 255, 255);
	static constexpr const colour_rgb_8u CYAN_2(0, 238, 238);
	static constexpr const colour_rgb_8u CYAN_3(0, 205, 205);
	static constexpr const colour_rgb_8u CYAN_4(0, 139, 139);
	static constexpr const colour_rgb_8u TEAL(0, 128, 128);
	static constexpr const colour_rgb_8u MEDIUM_TURQUOISE(72, 209, 204);
	static constexpr const colour_rgb_8u LIGHT_SEA_GREEN(32, 178, 170);
	static constexpr const colour_rgb_8u MANGANESE_BLUE(3, 168, 158);
	static constexpr const colour_rgb_8u TURQUOISE(64, 224, 208);
	static constexpr const colour_rgb_8u COLD_GREY(128, 138, 135);
	static constexpr const colour_rgb_8u TURQUOISE_BLUE(0, 199, 140);
	static constexpr const colour_rgb_8u AQUAMARINE_1(127, 255, 212);
	static constexpr const colour_rgb_8u AQUAMARINE_2(118, 238, 198);
	static constexpr const colour_rgb_8u AQUAMARINE_3(102, 205, 170);
	static constexpr const colour_rgb_8u AQUAMARINE_4(69, 139, 116);
	static constexpr const colour_rgb_8u MEDIUM_SPRING_GREEN(0, 250, 154);
	static constexpr const colour_rgb_8u MINT_CREAM(245, 255, 250);
	static constexpr const colour_rgb_8u SPRING_GREEN(0, 255, 127);
	static constexpr const colour_rgb_8u SPRING_GREEN_1(0, 238, 118);
	static constexpr const colour_rgb_8u SPRING_GREEN_2(0, 205, 102);
	static constexpr const colour_rgb_8u SPRING_GREEN_3(0, 139, 69);
	static constexpr const colour_rgb_8u MEDIUM_SEA_GREEN(60, 179, 113);
	static constexpr const colour_rgb_8u SEA_GREEN_1(84, 255, 159);
	static constexpr const colour_rgb_8u SEA_GREEN_2(78, 238, 148);
	static constexpr const colour_rgb_8u SEA_GREEN_3(67, 205, 128);
	static constexpr const colour_rgb_8u SEA_GREEN_4(46, 139, 87);
	static constexpr const colour_rgb_8u EMERALD_GREEN(0, 201, 87);
	static constexpr const colour_rgb_8u MINT(189, 252, 201);
	static constexpr const colour_rgb_8u COBALT_GREEN(61, 145, 64);
	static constexpr const colour_rgb_8u HONEYDEW_1(240, 255, 240);
	static constexpr const colour_rgb_8u HONEYDEW_2(224, 238, 224);
	static constexpr const colour_rgb_8u HONEYDEW_3(193, 205, 193);
	static constexpr const colour_rgb_8u HONEYDEW_4(131, 139, 131);
	static constexpr const colour_rgb_8u DARK_SEA_GREEN(143, 188, 143);
	static constexpr const colour_rgb_8u DARK_SEA_GREEN_1(193, 255, 193);
	static constexpr const colour_rgb_8u DARK_SEA_GREEN_2(180, 238, 180);
	static constexpr const colour_rgb_8u DARK_SEA_GREEN_3(155, 205, 155);
	static constexpr const colour_rgb_8u DARK_SEA_GREEN_4(105, 139, 105);
	static constexpr const colour_rgb_8u PALE_GREEN(152, 251, 152);
	static constexpr const colour_rgb_8u PALE_GREEN_1(154, 255, 154);
	static constexpr const colour_rgb_8u PALE_GREEN_2(144, 238, 144);
	static constexpr const colour_rgb_8u PALE_GREEN_3(124, 205, 124);
	static constexpr const colour_rgb_8u PALE_GREEN_4(84, 139, 84);
	static constexpr const colour_rgb_8u LIME_GREEN(50, 205, 50);
	static constexpr const colour_rgb_8u FOREST_GREEN(34, 139, 34);
	static constexpr const colour_rgb_8u GREEN_1(0, 255, 0);
	static constexpr const colour_rgb_8u GREEN_2(0, 238, 0);
	static constexpr const colour_rgb_8u GREEN_3(0, 205, 0);
	static constexpr const colour_rgb_8u GREEN_4(0, 139, 0);
	static constexpr const colour_rgb_8u GREEN(0, 128, 0);
	static constexpr const colour_rgb_8u DARK_GREEN(0, 100, 0);
	static constexpr const colour_rgb_8u SAP_GREEN(48, 128, 20);
	static constexpr const colour_rgb_8u LAWN_GREEN(124, 252, 0);
	static constexpr const colour_rgb_8u CHARTREUSE_1(127, 255, 0);
	static constexpr const colour_rgb_8u CHARTREUSE_2(118, 238, 0);
	static constexpr const colour_rgb_8u CHARTREUSE_3(102, 205, 0);
	static constexpr const colour_rgb_8u CHARTREUSE_4(69, 139, 0);
	static constexpr const colour_rgb_8u GREEN_YELLOW(173, 255, 47);
	static constexpr const colour_rgb_8u DARK_OLIVE_GREEN_1(202, 255, 112);
	static constexpr const colour_rgb_8u DARK_OLIVE_GREEN_2(188, 238, 104);
	static constexpr const colour_rgb_8u DARK_OLIVE_GREEN_3(162, 205, 90);
	static constexpr const colour_rgb_8u DARK_OLIVE_GREEN_4(110, 139, 61);
	static constexpr const colour_rgb_8u DARK_OLIVE_GREEN(85, 107, 47);
	static constexpr const colour_rgb_8u OLIVE_DRAB(107, 142, 35);
	static constexpr const colour_rgb_8u OLIVE_DRAB_1(192, 255, 62);
	static constexpr const colour_rgb_8u OLIVE_DRAB_2(179, 238, 58);
	static constexpr const colour_rgb_8u OLIVE_DRAB_3(154, 205, 50);
	static constexpr const colour_rgb_8u OLIVE_DRAB_4(105, 139, 34);
	static constexpr const colour_rgb_8u IVORY_1(255, 255, 240);
	static constexpr const colour_rgb_8u IVORY_2(238, 238, 224);
	static constexpr const colour_rgb_8u IVORY_3(205, 205, 193);
	static constexpr const colour_rgb_8u IVORY_4(139, 139, 131);
	static constexpr const colour_rgb_8u BEIGE(245, 245, 220);
	static constexpr const colour_rgb_8u LIGHT_YELLOW_1(255, 255, 224);
	static constexpr const colour_rgb_8u LIGHT_YELLOW_2(238, 238, 209);
	static constexpr const colour_rgb_8u LIGHT_YELLOW_3(205, 205, 180);
	static constexpr const colour_rgb_8u LIGHT_YELLOW_4(139, 139, 122);
	static constexpr const colour_rgb_8u LIGHT_GOLDENROD_YELLOW(250, 250, 210);
	static constexpr const colour_rgb_8u YELLOW_1(255, 255, 0);
	static constexpr const colour_rgb_8u YELLOW_2(238, 238, 0);
	static constexpr const colour_rgb_8u YELLOW_3(205, 205, 0);
	static constexpr const colour_rgb_8u YELLOW_4(139, 139, 0);
	static constexpr const colour_rgb_8u WARM_GREY(128, 128, 105);
	static constexpr const colour_rgb_8u OLIVE(128, 128, 0);
	static constexpr const colour_rgb_8u DARK_KHAKI(189, 183, 107);
	static constexpr const colour_rgb_8u KHAKI_1(255, 246, 143);
	static constexpr const colour_rgb_8u KHAKI_2(238, 230, 133);
	static constexpr const colour_rgb_8u KHAKI_3(205, 198, 115);
	static constexpr const colour_rgb_8u KHAKI_4(139, 134, 78);
	static constexpr const colour_rgb_8u KHAKI(240, 230, 140);
	static constexpr const colour_rgb_8u PALE_GOLDENROD(238, 232, 170);
	static constexpr const colour_rgb_8u LEMON_CHIFFON_1(255, 250, 205);
	static constexpr const colour_rgb_8u LEMON_CHIFFON_2(238, 233, 191);
	static constexpr const colour_rgb_8u LEMON_CHIFFON_3(205, 201, 165);
	static constexpr const colour_rgb_8u LEMON_CHIFFON_4(139, 137, 112);
	static constexpr const colour_rgb_8u LIGHT_GOLDENROD_1(255, 236, 139);
	static constexpr const colour_rgb_8u LIGHT_GOLDENROD_2(238, 220, 130);
	static constexpr const colour_rgb_8u LIGHT_GOLDENROD_3(205, 190, 112);
	static constexpr const colour_rgb_8u LIGHT_GOLDENROD_4(139, 129, 76);
	static constexpr const colour_rgb_8u BANANA(227, 207, 87);
	static constexpr const colour_rgb_8u GOLD_1(255, 215, 0);
	static constexpr const colour_rgb_8u GOLD_2(238, 201, 0);
	static constexpr const colour_rgb_8u GOLD_3(205, 173, 0);
	static constexpr const colour_rgb_8u GOLD_4(139, 117, 0);
	static constexpr const colour_rgb_8u CORNSILK_1(255, 248, 220);
	static constexpr const colour_rgb_8u CORNSILK_2(238, 232, 205);
	static constexpr const colour_rgb_8u CORNSILK_3(205, 200, 177);
	static constexpr const colour_rgb_8u CORNSILK_4(139, 136, 120);
	static constexpr const colour_rgb_8u GOLDENROD(218, 165, 32);
	static constexpr const colour_rgb_8u GOLDENROD_1(255, 193, 37);
	static constexpr const colour_rgb_8u GOLDENROD_2(238, 180, 34);
	static constexpr const colour_rgb_8u GOLDENROD_3(205, 155, 29);
	static constexpr const colour_rgb_8u GOLDENROD_4(139, 105, 20);
	static constexpr const colour_rgb_8u DARK_GOLDENROD(184, 134, 11);
	static constexpr const colour_rgb_8u DARK_GOLDENROD_1(255, 185, 15);
	static constexpr const colour_rgb_8u DARK_GOLDENROD_2(238, 173, 14);
	static constexpr const colour_rgb_8u DARK_GOLDENROD_3(205, 149, 12);
	static constexpr const colour_rgb_8u DARK_GOLDENROD_4(139, 101, 8);
	static constexpr const colour_rgb_8u ORANGE_1(255, 165, 0);
	static constexpr const colour_rgb_8u ORANGE_2(238, 154, 0);
	static constexpr const colour_rgb_8u ORANGE_3(205, 133, 0);
	static constexpr const colour_rgb_8u ORANGE_4(139, 90, 0);
	static constexpr const colour_rgb_8u FLORAL_WHITE(255, 250, 240);
	static constexpr const colour_rgb_8u OLD_LACE(253, 245, 230);
	static constexpr const colour_rgb_8u WHEAT(245, 222, 179);
	static constexpr const colour_rgb_8u WHEAT_1(255, 231, 186);
	static constexpr const colour_rgb_8u WHEAT_2(238, 216, 174);
	static constexpr const colour_rgb_8u WHEAT_3(205, 186, 150);
	static constexpr const colour_rgb_8u WHEAT_4(139, 126, 102);
	static constexpr const colour_rgb_8u MOCCASIN(255, 228, 181);
	static constexpr const colour_rgb_8u PAPAYA_WHIP(255, 239, 213);
	static constexpr const colour_rgb_8u BLANCHED_ALMOND(255, 235, 205);
	static constexpr const colour_rgb_8u NAVAJO_WHITE_1(255, 222, 173);
	static constexpr const colour_rgb_8u NAVAJO_WHITE_2(238, 207, 161);
	static constexpr const colour_rgb_8u NAVAJO_WHITE_3(205, 179, 139);
	static constexpr const colour_rgb_8u NAVAJO_WHITE_4(139, 121, 94);
	static constexpr const colour_rgb_8u EGGSHELL(252, 230, 201);
	static constexpr const colour_rgb_8u TAN(210, 180, 140);
	static constexpr const colour_rgb_8u BRICK(156, 102, 31);
	static constexpr const colour_rgb_8u CADMIUM_YELLOW(255, 153, 18);
	static constexpr const colour_rgb_8u ANTIQUE_WHITE(250, 235, 215);
	static constexpr const colour_rgb_8u ANTIQUE_WHITE_1(255, 239, 219);
	static constexpr const colour_rgb_8u ANTIQUE_WHITE_2(238, 223, 204);
	static constexpr const colour_rgb_8u ANTIQUE_WHITE_3(205, 192, 176);
	static constexpr const colour_rgb_8u ANTIQUE_WHITE_4(139, 131, 120);
	static constexpr const colour_rgb_8u BURLYWOOD(222, 184, 135);
	static constexpr const colour_rgb_8u BURLYWOOD_1(255, 211, 155);
	static constexpr const colour_rgb_8u BURLYWOOD_2(238, 197, 145);
	static constexpr const colour_rgb_8u BURLYWOOD_3(205, 170, 125);
	static constexpr const colour_rgb_8u BURLYWOOD_4(139, 115, 85);
	static constexpr const colour_rgb_8u BISQUE_1(255, 228, 196);
	static constexpr const colour_rgb_8u BISQUE_2(238, 213, 183);
	static constexpr const colour_rgb_8u BISQUE_3(205, 183, 158);
	static constexpr const colour_rgb_8u BISQUE_4(139, 125, 107);
	static constexpr const colour_rgb_8u MELON(227, 168, 105);
	static constexpr const colour_rgb_8u CARROT(237, 145, 33);
	static constexpr const colour_rgb_8u DARK_ORANGE(255, 140, 0);
	static constexpr const colour_rgb_8u DARK_ORANGE_1(255, 127, 0);
	static constexpr const colour_rgb_8u DARK_ORANGE_2(238, 118, 0);
	static constexpr const colour_rgb_8u DARK_ORANGE_3(205, 102, 0);
	static constexpr const colour_rgb_8u DARK_ORANGE_4(139, 69, 0);
	static constexpr const colour_rgb_8u ORANGE(255, 128, 0);
	static constexpr const colour_rgb_8u TAN_1(255, 165, 79);
	static constexpr const colour_rgb_8u TAN_2(238, 154, 73);
	static constexpr const colour_rgb_8u TAN_3(205, 133, 63);
	static constexpr const colour_rgb_8u TAN_4(139, 90, 43);
	static constexpr const colour_rgb_8u LINEN(250, 240, 230);
	static constexpr const colour_rgb_8u PEACHPUFF_1(255, 218, 185);
	static constexpr const colour_rgb_8u PEACHPUFF_2(238, 203, 173);
	static constexpr const colour_rgb_8u PEACHPUFF_3(205, 175, 149);
	static constexpr const colour_rgb_8u PEACHPUFF_4(139, 119, 101);
	static constexpr const colour_rgb_8u SEASHELL_1(255, 245, 238);
	static constexpr const colour_rgb_8u SEASHELL_2(238, 229, 222);
	static constexpr const colour_rgb_8u SEASHELL_3(205, 197, 191);
	static constexpr const colour_rgb_8u SEASHELL_4(139, 134, 130);
	static constexpr const colour_rgb_8u SANDY_BROWN(244, 164, 96);
	static constexpr const colour_rgb_8u RAW_SIENNA(199, 97, 20);
	static constexpr const colour_rgb_8u CHOCOLATE(210, 105, 30);
	static constexpr const colour_rgb_8u CHOCOLATE_1(255, 127, 36);
	static constexpr const colour_rgb_8u CHOCOLATE_2(238, 118, 33);
	static constexpr const colour_rgb_8u CHOCOLATE_3(205, 102, 29);
	static constexpr const colour_rgb_8u CHOCOLATE_4(139, 69, 19);
	static constexpr const colour_rgb_8u IVORY_BLACK(41, 36, 33);
	static constexpr const colour_rgb_8u FLESH(255, 125, 64);
	static constexpr const colour_rgb_8u CADMIUM_ORANGE(255, 97, 3);
	static constexpr const colour_rgb_8u BURNT_SIENNA(138, 54, 15);
	static constexpr const colour_rgb_8u SIENNA(160, 82, 45);
	static constexpr const colour_rgb_8u SIENNA_1(255, 130, 71);
	static constexpr const colour_rgb_8u SIENNA_2(238, 121, 66);
	static constexpr const colour_rgb_8u SIENNA_3(205, 104, 57);
	static constexpr const colour_rgb_8u SIENNA_4(139, 71, 38);
	static constexpr const colour_rgb_8u LIGHT_SALMON_1(255, 160, 122);
	static constexpr const colour_rgb_8u LIGHT_SALMON_2(238, 149, 114);
	static constexpr const colour_rgb_8u LIGHT_SALMON_3(205, 129, 98);
	static constexpr const colour_rgb_8u LIGHT_SALMON_4(139, 87, 66);
	static constexpr const colour_rgb_8u CORAL(255, 127, 80);
	static constexpr const colour_rgb_8u ORANGE_RED_1(255, 69, 0);
	static constexpr const colour_rgb_8u ORANGE_RED_2(238, 64, 0);
	static constexpr const colour_rgb_8u ORANGE_RED_3(205, 55, 0);
	static constexpr const colour_rgb_8u ORANGE_RED_4(139, 37, 0);
	static constexpr const colour_rgb_8u SEPIA(94, 38, 18);
	static constexpr const colour_rgb_8u DARK_SALMON(233, 150, 122);
	static constexpr const colour_rgb_8u SALMON_1(255, 140, 105);
	static constexpr const colour_rgb_8u SALMON_2(238, 130, 98);
	static constexpr const colour_rgb_8u SALMON_3(205, 112, 84);
	static constexpr const colour_rgb_8u SALMON_4(139, 76, 57);
	static constexpr const colour_rgb_8u CORAL_1(255, 114, 86);
	static constexpr const colour_rgb_8u CORAL_2(238, 106, 80);
	static constexpr const colour_rgb_8u CORAL_3(205, 91, 69);
	static constexpr const colour_rgb_8u CORAL_4(139, 62, 47);
	static constexpr const colour_rgb_8u BURNTUMBER(138, 51, 36);
	static constexpr const colour_rgb_8u TOMATO_1(255, 99, 71);
	static constexpr const colour_rgb_8u TOMATO_2(238, 92, 66);
	static constexpr const colour_rgb_8u TOMATO_3(205, 79, 57);
	static constexpr const colour_rgb_8u TOMATO_4(139, 54, 38);
	static constexpr const colour_rgb_8u SALMON(250, 128, 114);
	static constexpr const colour_rgb_8u MISTY_ROSE_1(255, 228, 225);
	static constexpr const colour_rgb_8u MISTY_ROSE_2(238, 213, 210);
	static constexpr const colour_rgb_8u MISTY_ROSE_3(205, 183, 181);
	static constexpr const colour_rgb_8u MISTY_ROSE_4(139, 125, 123);
	static constexpr const colour_rgb_8u SNOW_1(255, 250, 250);
	static constexpr const colour_rgb_8u SNOW_2(238, 233, 233);
	static constexpr const colour_rgb_8u SNOW_3(205, 201, 201);
	static constexpr const colour_rgb_8u SNOW_4(139, 137, 137);
	static constexpr const colour_rgb_8u ROSY_BROWN(188, 143, 143);
	static constexpr const colour_rgb_8u ROSY_BROWN_1(255, 193, 193);
	static constexpr const colour_rgb_8u ROSY_BROWN_2(238, 180, 180);
	static constexpr const colour_rgb_8u ROSY_BROWN_3(205, 155, 155);
	static constexpr const colour_rgb_8u ROSY_BROWN_4(139, 105, 105);
	static constexpr const colour_rgb_8u LIGHTCORAL(240, 128, 128);
	static constexpr const colour_rgb_8u INDIANRED(205, 92, 92);
	static constexpr const colour_rgb_8u INDIANRED_1(255, 106, 106);
	static constexpr const colour_rgb_8u INDIANRED_2(238, 99, 99);
	static constexpr const colour_rgb_8u INDIANRED_4(139, 58, 58);
	static constexpr const colour_rgb_8u INDIANRED_3(205, 85, 85);
	static constexpr const colour_rgb_8u BROWN(165, 42, 42);
	static constexpr const colour_rgb_8u BROWN_1(255, 64, 64);
	static constexpr const colour_rgb_8u BROWN_2(238, 59, 59);
	static constexpr const colour_rgb_8u BROWN_3(205, 51, 51);
	static constexpr const colour_rgb_8u BROWN_4(139, 35, 35);
	static constexpr const colour_rgb_8u FIRE_BRICK(178, 34, 34);
	static constexpr const colour_rgb_8u FIRE_BRICK_1(255, 48, 48);
	static constexpr const colour_rgb_8u FIRE_BRICK_2(238, 44, 44);
	static constexpr const colour_rgb_8u FIRE_BRICK_3(205, 38, 38);
	static constexpr const colour_rgb_8u FIRE_BRICK_4(139, 26, 26);
	static constexpr const colour_rgb_8u RED_1(255, 0, 0);
	static constexpr const colour_rgb_8u RED_2(238, 0, 0);
	static constexpr const colour_rgb_8u RED_3(205, 0, 0);
	static constexpr const colour_rgb_8u RED_4(139, 0, 0);
	static constexpr const colour_rgb_8u MAROON(128, 0, 0);
	static constexpr const colour_rgb_8u SGI_BEET(142, 56, 142);
	static constexpr const colour_rgb_8u SGI_SLATEBLUE(113, 113, 198);
	static constexpr const colour_rgb_8u SGI_LIGHTBLUE(125, 158, 192);
	static constexpr const colour_rgb_8u SGI_TEAL(56, 142, 142);
	static constexpr const colour_rgb_8u SGI_CHARTREUSE(113, 198, 113);
	static constexpr const colour_rgb_8u SGI_OLIVEDRAB(142, 142, 56);
	static constexpr const colour_rgb_8u SGI_BRIGHTGRAY(197, 193, 170);
	static constexpr const colour_rgb_8u SGI_SALMON(198, 113, 113);
	static constexpr const colour_rgb_8u SGI_DARKGRAY(85, 85, 85);
	static constexpr const colour_rgb_8u SGI_GRAY_12(30, 30, 30);
	static constexpr const colour_rgb_8u SGI_GRAY_16(40, 40, 40);
	static constexpr const colour_rgb_8u SGI_GRAY_32(81, 81, 81);
	static constexpr const colour_rgb_8u SGI_GRAY_36(91, 91, 91);
	static constexpr const colour_rgb_8u SGI_GRAY_52(132, 132, 132);
	static constexpr const colour_rgb_8u SGI_GRAY_56(142, 142, 142);
	static constexpr const colour_rgb_8u SGI_LIGHTGRAY(170, 170, 170);
	static constexpr const colour_rgb_8u SGI_GRAY_72(183, 183, 183);
	static constexpr const colour_rgb_8u SGI_GRAY_76(193, 193, 193);
	static constexpr const colour_rgb_8u SGI_GRAY_92(234, 234, 234);
	static constexpr const colour_rgb_8u SGI_GRAY_96(244, 244, 244);
	static constexpr const colour_rgb_8u WHITE(255, 255, 255);
	static constexpr const colour_rgb_8u WHITE_SMOKE(245, 245, 245);
	static constexpr const colour_rgb_8u GAINSBORO(220, 220, 220);
	static constexpr const colour_rgb_8u LIGHT_GREY(211, 211, 211);
	static constexpr const colour_rgb_8u SILVER(192, 192, 192);
	static constexpr const colour_rgb_8u DARK_GRAY(169, 169, 169);
	static constexpr const colour_rgb_8u GRAY(128, 128, 128);
	static constexpr const colour_rgb_8u DIM_GRAY(105, 105, 105);
	static constexpr const colour_rgb_8u BLACK(0, 0, 0);
	static constexpr const colour_rgb_8u GRAY_99(252, 252, 252);
	static constexpr const colour_rgb_8u GRAY_98(250, 250, 250);
	static constexpr const colour_rgb_8u GRAY_97(247, 247, 247);
	static constexpr const colour_rgb_8u GRAY_96(245, 245, 245);
	static constexpr const colour_rgb_8u GRAY_95(242, 242, 242);
	static constexpr const colour_rgb_8u GRAY_94(240, 240, 240);
	static constexpr const colour_rgb_8u GRAY_93(237, 237, 237);
	static constexpr const colour_rgb_8u GRAY_92(235, 235, 235);
	static constexpr const colour_rgb_8u GRAY_91(232, 232, 232);
	static constexpr const colour_rgb_8u GRAY_90(229, 229, 229);
	static constexpr const colour_rgb_8u GRAY_89(227, 227, 227);
	static constexpr const colour_rgb_8u GRAY_88(224, 224, 224);
	static constexpr const colour_rgb_8u GRAY_87(222, 222, 222);
	static constexpr const colour_rgb_8u GRAY_86(219, 219, 219);
	static constexpr const colour_rgb_8u GRAY_85(217, 217, 217);
	static constexpr const colour_rgb_8u GRAY_84(214, 214, 214);
	static constexpr const colour_rgb_8u GRAY_83(212, 212, 212);
	static constexpr const colour_rgb_8u GRAY_82(209, 209, 209);
	static constexpr const colour_rgb_8u GRAY_81(207, 207, 207);
	static constexpr const colour_rgb_8u GRAY_80(204, 204, 204);
	static constexpr const colour_rgb_8u GRAY_79(201, 201, 201);
	static constexpr const colour_rgb_8u GRAY_78(199, 199, 199);
	static constexpr const colour_rgb_8u GRAY_77(196, 196, 196);
	static constexpr const colour_rgb_8u GRAY_76(194, 194, 194);
	static constexpr const colour_rgb_8u GRAY_75(191, 191, 191);
	static constexpr const colour_rgb_8u GRAY_74(189, 189, 189);
	static constexpr const colour_rgb_8u GRAY_73(186, 186, 186);
	static constexpr const colour_rgb_8u GRAY_72(184, 184, 184);
	static constexpr const colour_rgb_8u GRAY_71(181, 181, 181);
	static constexpr const colour_rgb_8u GRAY_70(179, 179, 179);
	static constexpr const colour_rgb_8u GRAY_69(176, 176, 176);
	static constexpr const colour_rgb_8u GRAY_68(173, 173, 173);
	static constexpr const colour_rgb_8u GRAY_67(171, 171, 171);
	static constexpr const colour_rgb_8u GRAY_66(168, 168, 168);
	static constexpr const colour_rgb_8u GRAY_65(166, 166, 166);
	static constexpr const colour_rgb_8u GRAY_64(163, 163, 163);
	static constexpr const colour_rgb_8u GRAY_63(161, 161, 161);
	static constexpr const colour_rgb_8u GRAY_62(158, 158, 158);
	static constexpr const colour_rgb_8u GRAY_61(156, 156, 156);
	static constexpr const colour_rgb_8u GRAY_60(153, 153, 153);
	static constexpr const colour_rgb_8u GRAY_59(150, 150, 150);
	static constexpr const colour_rgb_8u GRAY_58(148, 148, 148);
	static constexpr const colour_rgb_8u GRAY_57(145, 145, 145);
	static constexpr const colour_rgb_8u GRAY_56(143, 143, 143);
	static constexpr const colour_rgb_8u GRAY_55(140, 140, 140);
	static constexpr const colour_rgb_8u GRAY_54(138, 138, 138);
	static constexpr const colour_rgb_8u GRAY_53(135, 135, 135);
	static constexpr const colour_rgb_8u GRAY_52(133, 133, 133);
	static constexpr const colour_rgb_8u GRAY_51(130, 130, 130);
	static constexpr const colour_rgb_8u GRAY_50(127, 127, 127);
	static constexpr const colour_rgb_8u GRAY_49(125, 125, 125);
	static constexpr const colour_rgb_8u GRAY_48(122, 122, 122);
	static constexpr const colour_rgb_8u GRAY_47(120, 120, 120);
	static constexpr const colour_rgb_8u GRAY_46(117, 117, 117);
	static constexpr const colour_rgb_8u GRAY_45(115, 115, 115);
	static constexpr const colour_rgb_8u GRAY_44(112, 112, 112);
	static constexpr const colour_rgb_8u GRAY_43(110, 110, 110);
	static constexpr const colour_rgb_8u GRAY_42(107, 107, 107);
	static constexpr const colour_rgb_8u GRAY_41(105, 105, 105);
	static constexpr const colour_rgb_8u GRAY_40(102, 102, 102);
	static constexpr const colour_rgb_8u GRAY_39(99, 99, 99);
	static constexpr const colour_rgb_8u GRAY_38(97, 97, 97);
	static constexpr const colour_rgb_8u GRAY_37(94, 94, 94);
	static constexpr const colour_rgb_8u GRAY_36(92, 92, 92);
	static constexpr const colour_rgb_8u GRAY_35(89, 89, 89);
	static constexpr const colour_rgb_8u GRAY_34(87, 87, 87);
	static constexpr const colour_rgb_8u GRAY_33(84, 84, 84);
	static constexpr const colour_rgb_8u GRAY_32(82, 82, 82);
	static constexpr const colour_rgb_8u GRAY_31(79, 79, 79);
	static constexpr const colour_rgb_8u GRAY_30(77, 77, 77);
	static constexpr const colour_rgb_8u GRAY_29(74, 74, 74);
	static constexpr const colour_rgb_8u GRAY_28(71, 71, 71);
	static constexpr const colour_rgb_8u GRAY_27(69, 69, 69);
	static constexpr const colour_rgb_8u GRAY_26(66, 66, 66);
	static constexpr const colour_rgb_8u GRAY_25(64, 64, 64);
	static constexpr const colour_rgb_8u GRAY_24(61, 61, 61);
	static constexpr const colour_rgb_8u GRAY_23(59, 59, 59);
	static constexpr const colour_rgb_8u GRAY_22(56, 56, 56);
	static constexpr const colour_rgb_8u GRAY_21(54, 54, 54);
	static constexpr const colour_rgb_8u GRAY_20(51, 51, 51);
	static constexpr const colour_rgb_8u GRAY_19(48, 48, 48);
	static constexpr const colour_rgb_8u GRAY_18(46, 46, 46);
	static constexpr const colour_rgb_8u GRAY_17(43, 43, 43);
	static constexpr const colour_rgb_8u GRAY_16(41, 41, 41);
	static constexpr const colour_rgb_8u GRAY_15(38, 38, 38);
	static constexpr const colour_rgb_8u GRAY_14(36, 36, 36);
	static constexpr const colour_rgb_8u GRAY_13(33, 33, 33);
	static constexpr const colour_rgb_8u GRAY_12(31, 31, 31);
	static constexpr const colour_rgb_8u GRAY_11(28, 28, 28);
	static constexpr const colour_rgb_8u GRAY_10(26, 26, 26);
	static constexpr const colour_rgb_8u GRAY_9(23, 23, 23);
	static constexpr const colour_rgb_8u GRAY_8(20, 20, 20);
	static constexpr const colour_rgb_8u GRAY_7(18, 18, 18);
	static constexpr const colour_rgb_8u GRAY_6(15, 15, 15);
	static constexpr const colour_rgb_8u GRAY_5(13, 13, 13);
	static constexpr const colour_rgb_8u GRAY_4(10, 10, 10);
	static constexpr const colour_rgb_8u GRAY_3(8, 8, 8);
	static constexpr const colour_rgb_8u GRAY_2(5, 5, 5);
	static constexpr const colour_rgb_8u GRAY_1(3, 3, 3);
}}

#endif