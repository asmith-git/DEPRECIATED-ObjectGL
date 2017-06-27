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
}}

#endif