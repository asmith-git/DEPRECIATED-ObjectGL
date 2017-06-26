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

#ifndef ASMITH_OPENGL_LIGHT_HPP
#define ASMITH_OPENGL_LIGHT_HPP

#include <memory>
#include "core.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief Wrapper class for OpenGL lighting
		\author Adam Smith
		\date Created : 26th June 2017 Modified 26th June 2017
		\version 1.0
	*/
	class light : public std::enable_shared_from_this<light> {
	private:
		vec4f mPosition;
		vec4f mAmbient;
		vec4f mDiffuse;
		vec4f mSpecular;
		vec3f mDirection;
		GLfloat mConstantAttenuation;
		GLfloat mLinearAttenuation;
		GLfloat mQuadraticAttenuation;
		GLint mExponent;
		GLint mCutoff;
		const GLenum mID;
		bool mEnabled;
	private:
		light(const light&) = delete;
		light(light&&) = delete;
		light& operator=(const light&) = delete;
		light& operator=(light&&) = delete;

		light(GLenum) throw();
	public:
		static std::shared_ptr<light> get_light(GLenum) throw();
		static void enable_lighting() throw();
		static void disable_lighting() throw();
		static bool is_lighting_enabled() throw();
		static void set_scene_ambient(const vec4f&) throw();
		static const vec4f& get_scene_ambient() throw();

		~light() throw();

		void enable() throw();
		void disable() throw();
		bool is_enabled() const throw();

		const vec4f& get_position() const throw();
		const vec4f& get_ambient() const throw();
		const vec4f& get_diffuse() const throw();
		const vec4f& get_specular() const throw();
		const vec3f& get_spot_direction() const throw();
		GLint get_spot_exponent() const throw();
		GLint get_spot_cutoff() const throw();
		GLfloat get_constant_attenuation() const throw();
		GLfloat get_linear_attenuation() const throw();
		GLfloat get_quadratic_attenuation() const throw();

		void set_position(const vec4f&) throw();
		void set_ambient(const vec4f&) throw();
		void set_diffuse(const vec4f&) throw();
		void set_specular(const vec4f&) throw();
		void set_spot_direction(const vec3f&) throw();
		void set_spot_exponent(GLint) throw();
		void set_spot_cutoff(GLint) throw();
		void set_constant_attenuation(GLfloat) throw();
		void set_linear_attenuation(GLfloat) throw();
		void set_quadratic_attenuation(GLfloat) throw();
	};

}}

#endif