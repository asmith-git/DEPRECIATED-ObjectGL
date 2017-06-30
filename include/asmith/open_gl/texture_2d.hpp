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
		\version 1.0
	*/
	class texture_2d : public object {
	private:
		vec4f mBorderColour;
		GLenum mTarget;
		GLint mLevel;
		GLint mInternalFormat;
		GLsizei mWidth;
		GLsizei mHeight;
		GLint mBorder;
		GLenum mFormat;
		GLenum mType;
		GLenum mWrap;
		GLenum mFilter;
		bool mMipmaps;
	public:
		texture_2d(context&) throw();
		~texture_2d() throw();

		GLenum get_target() const throw();
		GLint get_level() const throw();
		GLint get_internal_format() const throw();
		GLsizei get_width() const throw();
		GLsizei get_height() const throw();
		GLint get_border() const throw();
		GLenum get_format() const throw();
		GLenum get_type() const throw();
		GLenum get_wrap() const throw();
		GLenum get_filter() const throw();
		const vec4f& get_border_colour() const throw();
		bool has_mipmaps() const throw();

		void set_target(GLenum) throw();
		void set_level(GLint) throw();
		void set_internal_format(GLint) throw();
		void set_border(GLint) throw();
		void set_format(GLenum) throw();
		void set_type(GLenum) throw();
		void set_wrap(GLenum) throw();
		void set_filter(GLenum) throw();
		void set_border_colour(const vec4f&) throw();
		void set_mipmaps(bool) throw();

		void bind() throw();
		void load_raw(const void*, GLsizei, GLsizei) throw();

		template<class C>
		inline void load(const C* aData, GLsizei aWidth, GLsizei aHeight) {
			set_format(C::FORMAT);
			set_type(C::TYPE);
			set_internal_format(C::INTERNAL_FORMAT);
			load_raw(aData, aWidth, aHeight);
		}

		// Inherited from object 

		void create() override;
		void destroy() override;
	};

}}

#endif