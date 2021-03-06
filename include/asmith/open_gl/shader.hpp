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

#ifndef ASMITH_OPENGL_SHADER_HPP
#define ASMITH_OPENGL_SHADER_HPP

#include "object.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief Base class for OpenGL shader objects
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.2
	*/
	class shader : public object {
	public:
		enum type : GLenum{
			VERTEX						= GL_VERTEX_SHADER,
			GEOMETRY					= GL_GEOMETRY_SHADER,
			FRAGMENT					= GL_FRAGMENT_SHADER,
			#if ASMITH_GL_VERSION_MAJOR >= 4
				#if ASMITH_GL_VERSION_MINOR >= 3 || ASMITH_GL_VERSION_MAJOR > 4
					COMPUTE 			= GL_COMPUTE_SHADER,
				#endif
				TESSELLATION_CONTROL	= GL_TESS_CONTROL_SHADER,
				TESSELLATION_EVALUATION	= GL_TESS_EVALUATION_SHADER,
			#endif
		};
	private:
		const type mType;
		bool mCompiled;
	public:
		shader(context&, type);
		virtual ~shader();
		
		void compile(const char*);
		bool is_compiled() const throw();

		type get_type() const throw();

		virtual GLuint get_max_uniform_components() const throw() = 0;
		virtual GLuint get_max_uniform_blocks() const throw() = 0;
		virtual GLuint get_max_input_components() const throw() = 0;
		virtual GLuint get_max_output_components() const throw() = 0;
		virtual GLuint get_max_texture_image_units() const throw() = 0;
	};

	template<class T>
	static std::shared_ptr<shader> compile_shader(context& aContext, const char* aSource) {
		std::shared_ptr<shader> tmp(new T(aContext));
		tmp->compile(aSource);
		return tmp;
	}
	
	
	/*!
		\brief OpenGL fragment shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class fragment_shader : public shader {
	public:
		fragment_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_fragment_shader(context& aContext, const char* aSource) { return compile_shader<fragment_shader>(aContext, aSource); }
	
	/*!
		\brief OpenGL vertex shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class vertex_shader : public shader {
	public:
		vertex_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_vertex_shader(context& aContext, const char* aSource) { return compile_shader<vertex_shader>(aContext, aSource); }
	
	/*!
		\brief OpenGL geometry shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class geometry_shader : public shader {
	public:
		geometry_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_geometry_shader(context& aContext, const char* aSource) { return compile_shader<geometry_shader>(aContext, aSource); }
	
#if ASMITH_GL_VERSION_GE(4,3)
	/*!
		\brief OpenGL compute shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class compute_shader : public shader {
	public:
		compute_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_compute_shader(context& aContext, const char* aSource) { return compile_shader<compute_shader>(aContext, aSource); }
#endif
#if ASMITH_GL_VERSION_GE(4,0)
	/*!
		\brief OpenGL tessellation control shader shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class tessellation_control_shader : public shader {
	public:
		tessellation_control_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_tessellation_control_shader(context& aContext, const char* aSource) { return compile_shader<tessellation_control_shader>(aContext, aSource); }
	
	/*!
		\brief OpenGL tessellation evaluation shader shader
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.1
	*/
	class tessellation_evaluation_shader : public shader {
	public:
		tessellation_evaluation_shader(context&);
		// Inherited from shader

		GLuint get_max_uniform_components() const throw() override;
		GLuint get_max_uniform_blocks() const throw() override;
		GLuint get_max_input_components() const throw() override;
		GLuint get_max_output_components() const throw() override;
		GLuint get_max_texture_image_units() const throw() override;
	};

	inline static std::shared_ptr<shader> compile_tessellation_evaluation_shader(context& aContext, const char* aSource) { return compile_shader<tessellation_evaluation_shader>(aContext, aSource); }
#endif
}}

#endif