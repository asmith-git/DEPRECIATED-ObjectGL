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

#endif