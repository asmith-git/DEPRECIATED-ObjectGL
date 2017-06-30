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

#ifndef ASMITH_OPENGL_TEXTURE_2D_HPP
#define ASMITH_OPENGL_TEXTURE_2D_HPP

#include <memory>
#include "object.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief
		\author Adam Smith
		\date Created : 27th June 2017 Modified 27th June 2017
		\version 1.2
	*/
	class texture_2d : public object {
	private:
		vec4f mBorderColour;
		GLenum mTarget;
		GLsizei mWidth;
		GLsizei mHeight;
		GLenum mWrap;
		GLenum mFilter;
	public:
		texture_2d(context&) throw();
		~texture_2d() throw();

		GLsizei get_width() const throw();
		GLsizei get_height() const throw();
		GLenum get_wrap() const throw();
		GLenum get_filter() const throw();
		const vec4f& get_border_colour() const throw();
		bool has_mipmaps() const throw();

		void set_wrap(GLenum) throw();
		void set_filter(GLenum) throw();
		void set_border_colour(const vec4f&) throw();
		void generate_mipmaps() throw();

		void bind(GLenum);
		void unbind();
		bool is_bound(GLenum) const throw();

		void load_raw(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*) throw();

		template<class C>
		inline void load(const C* aData, GLsizei aWidth, GLsizei aHeight, GLint aInternalFormat = C::INTERNAL_FORMAT) {
			load_raw(0, aInternalFormat, aWidth, aHeight, C::FORMAT, C::TYPE, aData);
		}
	};

}}

#endif