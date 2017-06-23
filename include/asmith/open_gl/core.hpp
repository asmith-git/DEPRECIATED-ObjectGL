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

#ifndef ASMITH_OPENGL_CORE_HPP
#define ASMITH_OPENGL_CORE_HPP

#include "GL/glew.h"

#ifndef ASMITH_GL_VERSION_MAJOR
	#define ASMITH_GL_VERSION_MAJOR 4
	#define ASMITH_GL_VERSION_MINOR 0
#endif

#define ASMITH_GL_VERSION_GT(major, minor) (ASMITH_GL_VERSION_MAJOR > major) || (ASMITH_GL_VERSION_MAJOR == major && ASMITH_GL_VERSION_MINOR > minor)
#define ASMITH_GL_VERSION_GE(major, minor) (ASMITH_GL_VERSION_MAJOR > major) || (ASMITH_GL_VERSION_MAJOR == major && ASMITH_GL_VERSION_MINOR >= minor)
#define ASMITH_GL_VERSION_LT(major, minor) (ASMITH_GL_VERSION_MAJOR < major) || (ASMITH_GL_VERSION_MAJOR == major && ASMITH_GL_VERSION_MINOR < minor)
#define ASMITH_GL_VERSION_LE(major, minor) (ASMITH_GL_VERSION_MAJOR < major) || (ASMITH_GL_VERSION_MAJOR == major && ASMITH_GL_VERSION_MINOR <= minor)
#define ASMITH_GL_VERSION_EQ(major, minor) (ASMITH_GL_VERSION_MAJOR == major && ASMITH_GL_VERSION_MINOR == minor)
#define ASMITH_GL_VERSION_NEQ(major, minor) (ASMITH_GL_VERSION_MAJOR != major || ASMITH_GL_VERSION_MINOR != minor)

#ifdef ASMITH_GL_USE_GLM
#include "glm/glm.hpp"

namespace asmith { namespace gl {
	typedef glm::vec2 vec2f;
	typedef glm::vec3 vec3f;
	typedef glm::vec4 vec4f;
	typedef glm::ivec2 vec2i;
	typedef glm::ivec2 vec3i;
	typedef glm::ivec2 vec4i;
	typedef glm::uvec2 vec2u;
	typedef glm::uvec2 vec3u;
	typedef glm::uvec2 vec4u;
	typedef glm::mat2 mat2;
	typedef glm::mat3 mat3;
	typedef glm::mat4 mat4;
}}
#else
namespace asmith { namespace gl {
	typedef GLfloat vec2f[2];
	typedef GLfloat vec3f[3];
	typedef GLfloat vec4f[4];
	typedef GLint vec2i[2];
	typedef GLint vec3i[3];
	typedef GLint vec4i[4];
	typedef GLuint vec2u[2];
	typedef GLuint vec3u[3];
	typedef GLuint vec4u[4];
	typedef GLfloat mat2[2][2];
	typedef GLfloat mat3[3][3];
	typedef GLfloat mat4[4][4];
}}
#endif

#endif