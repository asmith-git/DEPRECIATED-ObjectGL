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

#include "asmith/open_gl/shader.hpp"
#include <string>

namespace asmith { namespace gl {
	
	// shader
	
	shader::shader():
		mSource(nullptr)
	{}
	
	shader::~shader(){
		if(is_created()) destroy();
	}
	
	void shader::set_source(const char* aSource) throw() {
		mSource = aSource;
	}

	void shader::create(){
		if(is_created()) destroy();
		if(mSource == nullptr) throw std::runtime_error("asmith::gl::shader::create : Shader source not set");
		
		const char* const source = mSource;
		mSource = nullptr;
		const GLenum type = static_cast<GLenum>(GetType());
		const GLint length = strlen(source);
         
		mID = glCreateShader(type);
		if(mID == Object::INVALID_ID) throw std::runtime_error("asmith::gl::shader::create : glCreateShader returned 0");
		glShaderSource(mID, 1, &source, &length);
		glCompileShader(mID);
         
		GLint status = 0;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE){
		 	GLint logLength = 0;
		 	glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &logLength);
         
		 	std::string log(logLength, '\0');
		 	glGetShaderInfoLog(mID, logLength, &logLength, &log[0]);
        
		 	destroy();
         
		 	throw std::runtime_error(std::string("asmith::gl::shader::create : Compilation error : ") + log.c_str());
		}
	}

	void shader::destroy(){
		if(is_created()) {
			glDeleteShader(mID);
			mID = 0;
		}
	}

}}

#endif