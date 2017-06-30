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
	
	shader::shader(context& aContext, type aType):
		object(aContext),
		mType(aType),
		mCompiled(false)
	{
		mID = glCreateShader(mType);
		if (mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::shader::create : glCreateShader returned 0");
	}
	
	shader::~shader(){
		if(mID != 0) {
			glDeleteShader(mID);
			mID = 0;
			mCompiled = false;
		}
	}

	shader::type shader::get_type() const throw() {
		return mType;
	}
	
	void shader::compile(const char* aSource) {
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
         
		 	throw std::runtime_error(std::string("asmith::gl::shader::create : Compilation error : ") + log.c_str());
		}
		mCompiled = true;
	}

	bool shader::is_compiled() const throw() {
		return mCompiled;
	}
	
	// fragment_shader
	
	fragment_shader::fragment_shader(context& aContext) :
		shader(aContext, FRAGMENT)
	{}
	
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
	
	vertex_shader::vertex_shader(context& aContext) :
		shader(aContext, VERTEX)
	{}
	
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
	
	geometry_shader::geometry_shader(context& aContext) :
		shader(aContext, GEOMETRY)
	{}
	
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
	
	compute_shader::compute_shader(context& aContext) :
		shader(aContext, COMPUTE)
	{}
	
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
	
	tessellation_control_shader::tessellation_control_shader(context& aContext) :
		shader(aContext, TESSELLATION_CONTROL)
	{}
	
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
	
	tessellation_evaluation_shader::tessellation_evaluation_shader(context& aContext) :
		shader(aContext, TESSELLATION_EVALUATION)
	{}
	
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