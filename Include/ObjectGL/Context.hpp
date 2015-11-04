#ifndef OBJECT_GL_CONTEXT_HPP
#define OBJECT_GL_CONTEXT_HPP

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

#include "..\GLLoadGen\gl_core_3_3.h"
#include "..\GL\freeglut.h"

/*!
	\file Context.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{
	
	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	class Context{
	private:
		const GLuint mVersionMajor;
		const GLuint mVersionMinor;
	private:
		Context(const Context&);
		Context(Context&&);
		Context& operator=(const Context&);
		Context& operator=(Context&&);
	public:
		Context(const GLuint, const GLuint);
		~Context();

		GLuint GetVersionMajor() const;
		GLuint GetVersionMinor() const;
	};

}

#include "Context.inl"

#endif
