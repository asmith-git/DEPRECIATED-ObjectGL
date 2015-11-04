#ifndef OBJECT_GL_CONTEXT_INL
#define OBJECT_GL_CONTEXT_INL

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : $objectgl_email
// GitHub repository : $objectgl_git

/*!
	\file Context.inl
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{

	static bool GLUT_INIT = false;

	// Context

	Context::Context(const GLuint aVersionMajor, const GLuint aVersionMinor):
		mVersionMajor(aVersionMajor),
		mVersionMinor(aVersionMinor)
	{
		if (!GLUT_INIT){
			int argc = 0;
			glutInit(&argc, 0);
		}
	}

	Context::~Context(){
		
	}

	GLuint Context::GetVersionMajor() const{
		return mVersionMajor;
	}

	GLuint Context::GetVersionMinor() const{
		return mVersionMinor;
	}


}

#endif
