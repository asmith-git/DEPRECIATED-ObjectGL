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

#ifndef ASMITH_OPENGL_PROGRAM_HPP
#define ASMITH_OPENGL_PROGRAM_HPP

#include <vector>
#include "shader.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief OpenGL program
		\author Adam Smith
		\date Created : 6th November 2015 Modified 30th June 2017
		\version 2.3
	*/
	class program : public object {
	public:
		enum id_t : GLuint{
			INVALID_ID = 0
		};
	private:
		std::vector<std::shared_ptr<shader>> mShaders;
		std::shared_ptr<program> mPreviousBind;
		bool mBound;
	public:
		program(context&);
		~program();

		void attach(std::shared_ptr<shader>);
		void detach(std::shared_ptr<shader>);
		size_t shader_count() const throw();
		std::shared_ptr<shader> get_shader(size_t) const throw();
		
		void bind();
		void unbind();
		bool is_bound() const throw();
		bool is_currently_bound() const throw();

		GLint get_uniform_location(const GLchar*) const;

		void set_uniform(GLint, GLfloat);
		void set_uniform(GLint, GLfloat, GLfloat);
		void set_uniform(GLint, GLfloat, GLfloat, GLfloat);
		void set_uniform(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
		void set_uniform(GLint, GLint);
		void set_uniform(GLint, GLint, GLint);
		void set_uniform(GLint, GLint, GLint, GLint);
		void set_uniform(GLint, GLint, GLint, GLint, GLint);
		void set_uniform(GLint, GLuint);
		void set_uniform(GLint, GLuint, GLuint);
		void set_uniform(GLint, GLuint, GLuint, GLuint);
		void set_uniform(GLint, GLuint, GLuint, GLuint, GLuint);
		void set_uniform(GLint, const vec2f&);
		void set_uniform(GLint, const vec3f&);
		void set_uniform(GLint, const vec4f&);
		void set_uniform(GLint, const vec2i&);
		void set_uniform(GLint, const vec3i&);
		void set_uniform(GLint, const vec4i&);
		void set_uniform(GLint, const vec2u&);
		void set_uniform(GLint, const vec3u&);
		void set_uniform(GLint, const vec4u&);
		void set_uniform(GLint, const mat2&, GLboolean aTranspose = GL_FALSE);
		void set_uniform(GLint, const mat3&, GLboolean aTranspose = GL_FALSE);
		void set_uniform(GLint, const mat4&, GLboolean aTranspose = GL_FALSE);

		void get_uniform(GLint, GLfloat&) const;
		void get_uniform(GLint, GLint&) const;
		void get_uniform(GLint, GLuint&) const;
		void get_uniform(GLint, vec2f&) const;
		void get_uniform(GLint, vec3f&) const;
		void get_uniform(GLint, vec4f&) const;
		void get_uniform(GLint, vec2i&) const;
		void get_uniform(GLint, vec3i&) const;
		void get_uniform(GLint, vec4i&) const;
		void get_uniform(GLint, vec2u&) const;
		void get_uniform(GLint, vec3u&) const;
		void get_uniform(GLint, vec4u&) const;
		void get_uniform(GLint, mat2&) const;
		void get_uniform(GLint, mat3&) const;
		void get_uniform(GLint, mat4&) const;
		
		// Inherited from object
		void create() override;
		void destroy() override;
	};

	static std::shared_ptr<program> link_program(const std::vector<std::shared_ptr<shader>>& aShaders) {
		std::shared_ptr<program> tmp(new program(aShaders[0]->get_context()));
		for(const std::shared_ptr<shader>& i : aShaders) tmp->attach(i);
		tmp->create();
		return tmp;
	}

	/*!
		\brief OpenGL uniform value helper
		\author Adam Smith
		\date Created :  23rd June 2017 Modified 23rd June 2017
		\version 1.0
	*/
	template<class T>
	class uniform {
	private:
		std::shared_ptr<program> mProgram;
		T mValue;
		GLint mLocation;
	public:
		uniform(std::shared_ptr<program> aProgram, const GLchar* aName) :
			mProgram(aProgram),
			mLocation(-1)
		{
			mLocation = mProgram->get_uniform_location(aName);
			if(mLocation != -1) {
				mProgram->get_uniform(mLocation, mValue);
			}
		}

		inline T get() const throw() {
			return mValue;
		}

		inline bool set(const T& aValue) throw() {
			if(mLocation == -1) return false;
			mValue = aValue;
			mProgram->set_uniform(mLocation, aValue);
			return true;
		}

		inline uniform<T>& operator=(const T& aValue) throw() {
			set(aValue);
			return *this;
		}

		inline operator T() const throw() {
			return get();
		}
	};
}}

#endif
