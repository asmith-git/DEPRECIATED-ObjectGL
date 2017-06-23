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

#include "asmith/open_gl/program.hpp"
#include <string>

namespace asmith { namespace gl {
	
	std::vector<std::shared_ptr<object>> PROGRAM_BIND_STACK;
	
	// program
	
	program::~program() {
		while(is_bound()) {
			unbind();
		}
	}

	void program::attach(std::shared_ptr<shader> aShader) {
		if(is_created()) throw std::runtime_error("asmith::gl::program::attach : Shaders can only be attached before program is linked");
		mShaders.push_back(aShader);
	}

	void program::detach(std::shared_ptr<shader> aShader) {
		if(is_created()) throw std::runtime_error("asmith::gl::program::detach : Shaders can only be detached before program is linked");
		const auto end = mShaders.end();
		const auto i = std::find(mShaders.begin(), end, aShader);
		if(i != end) mShaders.erase(i);
	}

	size_t program::shader_count() const throw() {
		return mShaders.size();
	}

	std::shared_ptr<shader> program::get_shader(size_t aIndex) const throw() {
		if(aIndex >= mShaders.size()) return std::shared_ptr<shader>();
		else return mShaders[aIndex];
	}

	void program::bind() {
		PROGRAM_BIND_STACK.push_back(shared_from_this());
		glUseProgram(mID);
	}

	void program::unbind() {
		std::shared_ptr<object> tmp = shared_from_this();
		if(PROGRAM_BIND_STACK.back() == tmp) {
			PROGRAM_BIND_STACK.pop_back();
			glUseProgram(PROGRAM_BIND_STACK.empty() ? 0 : PROGRAM_BIND_STACK.back()->get_id());
		}else {
			const auto end = PROGRAM_BIND_STACK.rend();
			const auto i = std::find(PROGRAM_BIND_STACK.rbegin(), end, shared_from_this());
			if(i == end) throw std::runtime_error("asmith::gl::program::unbind : Program is not bound");
			//PROGRAM_BIND_STACK.erase(i);
			//! \todo Erase program from binding stack
		}
	}

	bool program::is_bound() const {
		const auto end = PROGRAM_BIND_STACK.end();
		const auto i = std::find(PROGRAM_BIND_STACK.begin(), end, shared_from_this());
		return i != end;
	}

	bool program::is_currently_bound() const throw() {
		return PROGRAM_BIND_STACK.back() == shared_from_this();
	}

	void program::create() {
		if(is_created()) destroy();
		
		mID = glCreateProgram();
		if(mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::program::destroy : glCreateProgram returned 0");
		
		for(const std::shared_ptr<shader>& i : mShaders){
			glAttachShader(mID, static_cast<GLuint>(i->get_id()));
		}
        
		glLinkProgram(mID);
        
		GLint status = 0;
		glGetProgramiv(mID, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			GLint logLength = 0;
			glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &logLength);
        
			std::string log(logLength, '\0');
			glGetProgramInfoLog(mID, logLength, &logLength, &log[0]);
        
			destroy();
        
			throw std::runtime_error(std::string("asmith::gl::program::create : Link error : ") + log.c_str());
		}
		
		for(const std::shared_ptr<shader>& i : mShaders){
			glDetachShader(mID, static_cast<GLuint>(i->get_id()));
		}
	}

	void program::destroy() {
		if(! is_created()) throw std::runtime_error("asmith::gl::program::destroy : Program has not been linked");
		glDeleteProgram(mID);
		mID = 0;
	}

	GLint program::get_uniform_location(const GLchar* aName) const {
		if(! is_created()) throw std::runtime_error("asmith::gl::program::get_uniform_location : Program has not been linked");
		return glGetUniformLocation(mID, aName);
	}


	void program::set_uniform(GLint aLocation, GLfloat a) {
		glUniform1f(aLocation, a);
	}

	void program::set_uniform(GLint aLocation, GLfloat a, GLfloat b) {
		glUniform2f(aLocation, a, b);
	}

	void program::set_uniform(GLint aLocation, GLfloat a, GLfloat b, GLfloat c) {
		glUniform3f(aLocation, a, b, c);
	}

	void program::set_uniform(GLint aLocation, GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
		glUniform4f(aLocation, a, b, c, d);
	}

	void program::set_uniform(GLint aLocation, GLint a) {
		glUniform1i(aLocation, a);
	}

	void program::set_uniform(GLint aLocation, GLint a, GLint b) {
		glUniform2i(aLocation, a, b);
	}

	void program::set_uniform(GLint aLocation, GLint a, GLint b, GLint c) {
		glUniform3i(aLocation, a, b, c);
	}

	void program::set_uniform(GLint aLocation, GLint a, GLint b, GLint c, GLint d) {
		glUniform4i(aLocation, a, b, c, d);
	}

	void program::set_uniform(GLint aLocation, GLuint a) {
		glUniform1ui(aLocation, a);
	}

	void program::set_uniform(GLint aLocation, GLuint a, GLuint b) {
		glUniform2ui(aLocation, a, b);
	}

	void program::set_uniform(GLint aLocation, GLuint a, GLuint b, GLuint c) {
		glUniform3ui(aLocation, a, b, c);
	}

	void program::set_uniform(GLint aLocation, GLuint a, GLuint b, GLuint c, GLuint d) {
		glUniform4ui(aLocation, a, b, c, d);
	}

	void program::set_uniform(GLint aLocation, const vec2f& aValue) {
		glUniform2fv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec3f& aValue) {
		glUniform3fv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec4f& aValue) {
		glUniform4fv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec2i& aValue) {
		glUniform2iv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec3i& aValue) {
		glUniform3iv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec4i& aValue) {
		glUniform4iv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec2u& aValue) {
		glUniform2uiv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec3u& aValue) {
		glUniform3uiv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const vec4u& aValue) {
		glUniform4uiv(aLocation, 1, &aValue[0]);
	}

	void program::set_uniform(GLint aLocation, const mat2& aValue, GLboolean aTranspose) {
		glUniformMatrix2fv(aLocation, 1, aTranspose, &aValue[0][0]);
	}

	void program::set_uniform(GLint aLocation, const mat3& aValue, GLboolean aTranspose) {
		glUniformMatrix3fv(aLocation, 1, aTranspose, &aValue[0][0]);
	}

	void program::set_uniform(GLint aLocation, const mat4& aValue, GLboolean aTranspose) {
		glUniformMatrix4fv(aLocation, 1, aTranspose, &aValue[0][0]);
	}

	//! \todo 2x3, 3x2, 2x4, 4x2, 3x4 and 4x3 matrix support

}}