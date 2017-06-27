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

	
	template<const GLenum F, const GLenum T, class ENABLE = void>
	struct colour {
		enum : GLenum {
			FORMAT = F,
			TYPE = T
		};
	};

	template<const GLenum T>
	struct colour<GL_RED, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RED,
			TYPE = T
		};

		type r;
	};

	template<const GLenum T>
	struct colour<GL_RG, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RG,
			TYPE = T
		};

		type r;
		type g;
	};

	template<const GLenum T>
	struct colour<GL_RGB, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RGB,
			TYPE = T
		};

		type r;
		type g;
		type b;
	};

	template<const GLenum T>
	struct colour<GL_RGBA, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_RGBA,
			TYPE = T
		};

		type r;
		type g;
		type b;
		type a;
	};

	template<const GLenum T>
	struct colour<GL_BGR, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_BGR,
			TYPE = T
		};

		type b;
		type g;
		type r;
	};

	template<const GLenum T>
	struct colour<GL_BGRA, T, typename std::enable_if<is_primative_type(T)>::type> {
		typedef enum_to_type<T> type;
		enum : GLenum {
			FORMAT = GL_BGRA,
			TYPE = T
		};

		type b;
		type g;
		type r;
		type a;
	};
}}

#endif