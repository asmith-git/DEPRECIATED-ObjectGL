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

#include "asmith/open_gl/texture_2d.hpp"
#include <stdexcept>

namespace asmith { namespace gl {
	//texture_2d

	texture_2d::texture_2d(context& aContext) throw() :
		object(aContext),
		mBorderColour(0.f, 0.f, 0.f, 1.f),
		mTarget(GL_INVALID_ENUM),
		mWidth(0),
		mHeight(0),
		mWrap(GL_CLAMP_TO_BORDER),
		mFilter(GL_LINEAR)
	{
		glGenTextures(1, &mID);
		if(mID == 0) throw std::runtime_error("asmith::gl::texture_2d::texture_2d : glGenTextures returned 0");
	}

	texture_2d::~texture_2d() throw() {
		if(mID == 0) return;
		glDeleteTextures(1, &mID);
		mID = 0;
	}

	GLsizei texture_2d::get_width() const throw() {
		return mWidth;
	}

	GLsizei texture_2d::get_height() const throw() {
		return mHeight;
	}

	const vec4f& texture_2d::get_border_colour() const throw() {
		return mBorderColour;
	}

	GLenum texture_2d::get_filter() const throw() {
		return mFilter;
	}

	GLenum texture_2d::get_wrap() const throw() {
		return mWrap;
	}

	void texture_2d::set_border_colour(const vec4f& aValue) throw() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::set_border_colour : Texture is not bound");
		memcpy(&mBorderColour[0], &aValue[0], 4 * sizeof(GLfloat));
		glTexParameterfv(mTarget, GL_TEXTURE_BORDER_COLOR, &mBorderColour[0]);
	}

	void texture_2d::set_filter(GLenum aValue) throw() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::set_filter : Texture is not bound");
		mFilter = aValue;
		glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, mFilter);
		glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, mFilter);
	}

	void texture_2d::set_wrap(GLenum aValue) throw() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::set_wrap : Texture is not bound");
		mWrap = aValue;
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, mWrap);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, mWrap);
	}

	void texture_2d::generate_mipmaps() throw() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::generate_mipmaps : Texture is not bound");
		glGenerateMipmap(mTarget);
	}

	void texture_2d::bind(GLenum aTarget) {
		if(mTarget != GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::bind : Texture is already bound");
		//! \todo Implement binding stack
		mTarget = aTarget;
		glBindTexture(mTarget, mID);
	}

	void texture_2d::unbind() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::unbind : Texture is not bound");
		//! \todo Implement binding stack
		glBindTexture(mTarget, 0);
		mTarget = GL_INVALID_ENUM;
	}

	bool texture_2d::is_bound(GLenum aTarget) const throw() {
		return mTarget == aTarget;
	}

	void texture_2d::load_raw(GLint aLevel, GLint aInternalFormat, GLsizei aWidth, GLsizei aHeight, GLenum aFormat, GLenum aType, const GLvoid* aValue) throw() {
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::texture_2d::load_raw : Texture is not bound");
		mWidth = aWidth;
		mHeight = aHeight;
		glTexImage2D(mTarget, aLevel, aInternalFormat, aWidth, aHeight, 0, aFormat, aType, aValue);
	}

}}