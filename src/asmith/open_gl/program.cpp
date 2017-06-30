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
#include "asmith/open_gl/context_state.hpp"

namespace asmith { namespace gl {
	
	// program
	
	program::program(context& aContext) :
		object(aContext),
		mBound(false)
	{}
	
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
		if(is_bound()) throw std::runtime_error("asmith::gl::program::bind : Program is already bound");
		mPreviousBind = mContext.state->currently_bound_program;
		mContext.state->currently_bound_program = std::static_pointer_cast<program>(shared_from_this());
		mBound = true;
		glUseProgram(mID);
	}

	void program::unbind() {
		if(! is_bound()) throw std::runtime_error("asmith::gl::program::unbind : Program is not bound");
		if(! is_currently_bound()) throw std::runtime_error("asmith::gl::program::unbind : Program is not the currently bound program"); //! \todo Unbinding of programs that are not current

		if(mPreviousBind) {
			glUseProgram(mPreviousBind->get_id());
			mContext.state->currently_bound_program.swap(mPreviousBind);
			mPreviousBind.swap(std::shared_ptr<program>());
		}else {
			glUseProgram(0);
			mContext.state->currently_bound_program.swap(std::shared_ptr<program>());
			mPreviousBind.swap(std::shared_ptr<program>());
		}
		mBound = false;
	}

	bool program::is_bound() const {
		return mBound;
	}

	bool program::is_currently_bound() const throw() {
		return mContext.state->currently_bound_program == shared_from_this();
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

	void program::get_uniform(GLint aLocation, GLfloat& aValue) const {
		glGetUniformfv(mID, 1, &aValue);
	}

	void program::get_uniform(GLint aLocation, GLint& aValue) const {
		glGetUniformiv(mID, 1, &aValue);
	}

	void program::get_uniform(GLint aLocation, GLuint& aValue) const {
		glGetUniformuiv(mID, 1, &aValue);
	}

	void program::get_uniform(GLint aLocation, vec2f& aValue) const {
		glGetUniformfv(mID, 2, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec3f& aValue) const {
		glGetUniformfv(mID, 3, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec4f& aValue) const {
		glGetUniformfv(mID, 4, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec2i& aValue) const {
		glGetUniformiv(mID, 2, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec3i& aValue) const {
		glGetUniformiv(mID, 3, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec4i& aValue) const {
		glGetUniformiv(mID, 4, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec2u& aValue) const {
		glGetUniformuiv(mID, 2, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec3u& aValue) const {
		glGetUniformuiv(mID, 3, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, vec4u& aValue) const {
		glGetUniformuiv(mID, 4, &aValue[0]);
	}

	void program::get_uniform(GLint aLocation, mat2& aValue) const {
		glGetUniformfv(mID, 2*2, &aValue[0][0]);
	}

	void program::get_uniform(GLint aLocation, mat3& aValue) const {
		glGetUniformfv(mID, 3*3, &aValue[0][0]);
	}

	void program::get_uniform(GLint aLocation, mat4& aValue) const {
		glGetUniformfv(mID, 4*4, &aValue[0][0]);
	}

	//! \todo 2x3, 3x2, 2x4, 4x2, 3x4 and 4x3 matrix support

}}