#ifndef OBJECT_GL_SHADER_INL
#define OBJECT_GL_SHADER_INL

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
	\file Shader.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <string>

namespace ObjectGL{

	// Shader

	Shader::Shader(Context& aContext, SourceFactory& aSource):
		Object(aContext),
		mSource(aSource)
	{}

	Shader::~Shader(){
		if(IsCreated()) Destroy();
	}

	void Shader::Create(){
		if(IsCreated()) throw std::runtime_error("ObjectGL::Shader : Shader has already been compiled");

		SourceFactory::Guard guard(mSource);
		const GLenum type = static_cast<GLenum>(GetType());
		const char* const source = mSource.Get();
		const GLint length = std::strlen(source);

		mID = glCreateShader(type);
		glShaderSource(mID, 1, &source, &length);
		glCompileShader(mID);

		GLint status = 0;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE){
			GLint logLength = 0;
			glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &logLength);

			std::string log(logLength, '\0');
			glGetShaderInfoLog(mID, logLength, &logLength, &log[0]);

			glDeleteShader(mID);
			mID = 0;

			throw std::runtime_error(std::string("ObjectGL::Shader : Failed to compile shader source : ") + log.c_str());
		}
	}

	void Shader::Destroy(){
		if (IsCreated()) throw std::runtime_error("ObjectGL::Shader : Shader has not been compiled");

		glDeleteShader(mID);
		mID = 0;
	}

}

#endif
