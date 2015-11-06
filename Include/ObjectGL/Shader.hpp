#ifndef OBJECT_GL_SHADER_HPP
#define OBJECT_GL_SHADER_HPP

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

#include "Object.hpp"

/*!
	\file Shader.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL{

	class Program;
	
	/*!
		\brief
		\author Adam Smith
		\date 6th November 2015
		\version 1.0
	*/
	class Shader : public Object{
	public:
		friend Program;
	public:
		Shader(Context& aContext);
		virtual ~Shader();

		virtual GLenum GetType() const = 0;

		virtual GLuint GetMaxUniformComponents() const = 0;
		virtual GLuint GetMaxUniformBlocks() const = 0;
		virtual GLuint GetMaxInputComponents() const = 0;
		virtual GLuint GetMaxOutputComponents() const = 0;
		virtual GLuint GetMaxTextureImageUnits() const = 0;
		virtual GLuint GetMaxImageUniforms() const = 0;

		// Inherited from Object

		virtual void Create();
		virtual void Destroy();
	};

}

#include "Shader.inl"

#endif
