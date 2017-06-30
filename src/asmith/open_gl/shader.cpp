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
		mLinked(false)
	{}
	
	shader::~shader(){
		
	}
	
	void shader::link(const char* aSource) {
		const GLint length = strlen(aSource);
		glShaderSource(mID, 1, &aSource, &length);
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
		mLinked = true;
	}

	bool shader::is_linked() const throw() {
		return mLinked;
	}

	void shader::create(){
		if(is_created()) destroy();
		mID = glCreateShader(static_cast<GLenum>(get_type()));
		if(mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::shader::create : glCreateShader returned 0");
	}

	void shader::destroy(){
		if(is_created()) {
			glDeleteShader(mID);
			mID = 0;
			mLinked = false;
		}
	}
	
	// fragment_shader
		
	shader::type fragment_shader::get_type() const {
		return FRAGMENT;
	}
	
	GLuint fragment_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint fragment_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint fragment_shader::get_max_input_components() const throw() {
		return GL_MAX_FRAGMENT_INPUT_COMPONENTS;
	}
	
	GLuint fragment_shader::get_max_output_components() const throw() {
		return 0;
	}
	
	GLuint fragment_shader::get_max_texture_image_units() const throw() {
		return 0;
	}
	
	// vertex_shader
		
	shader::type vertex_shader::get_type() const {
		return VERTEX;
	}
	
	GLuint vertex_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint vertex_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint vertex_shader::get_max_input_components() const throw() {
		return 0;
	}
	
	GLuint vertex_shader::get_max_output_components() const throw() {
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}
	
	GLuint vertex_shader::get_max_texture_image_units() const throw() {
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}
	
	// geometry_shader
		
	shader::type geometry_shader::get_type() const {
		return GEOMETRY;
	}
	
	GLuint geometry_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint geometry_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint geometry_shader::get_max_input_components() const throw() {
		return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
	}
	
	GLuint geometry_shader::get_max_output_components() const throw() {
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}
	
	GLuint geometry_shader::get_max_texture_image_units() const throw() {
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}

#if ASMITH_GL_VERSION_GE(4,3)
	// compute_shader
		
	shader::type compute_shader::get_type() const {
		return COMPUTE;
	}
	
	GLuint compute_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint compute_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint compute_shader::get_max_input_components() const throw() {
		return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
	}
	
	GLuint compute_shader::get_max_output_components() const throw() {
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}
	
	GLuint compute_shader::get_max_texture_image_units() const throw() {
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}
#endif
#if ASMITH_GL_VERSION_GE(4,0)
	// tessellation_control_shader
		
	shader::type tessellation_control_shader::get_type() const {
		return TESSELLATION_CONTROL;
	}
	
	GLuint tessellation_control_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint tessellation_control_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint tessellation_control_shader::get_max_input_components() const throw() {
		return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
	}
	
	GLuint tessellation_control_shader::get_max_output_components() const throw() {
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}
	
	GLuint tessellation_control_shader::get_max_texture_image_units() const throw() {
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}
	
	// tessellation_evaluation_shader
		
	shader::type tessellation_evaluation_shader::get_type() const {
		return TESSELLATION_EVALUATION;
	}
	
	GLuint tessellation_evaluation_shader::get_max_uniform_components() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
	}
	
	GLuint tessellation_evaluation_shader::get_max_uniform_blocks() const throw() {
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
	}
	
	GLuint tessellation_evaluation_shader::get_max_input_components() const throw() {
		return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
	}
	
	GLuint tessellation_evaluation_shader::get_max_output_components() const throw() {
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}
	
	GLuint tessellation_evaluation_shader::get_max_texture_image_units() const throw() {
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}
#endif

}}