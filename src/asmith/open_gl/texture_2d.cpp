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

namespace asmith { namespace gl {
	//texture_2d

	texture_2d::texture_2d(context& aContext) throw() :
		object(aContext),
		mBorderColour(0.f, 0.f, 0.f, 1.f),
		mTarget(GL_TEXTURE_2D),
		mInternalFormat(GL_RGB),
		mLevel(0),
		mWidth(0),
		mHeight(0),
		mBorder(0),
		mFormat(GL_RGB),
		mType(GL_FLOAT),
		mWrap(GL_CLAMP_TO_BORDER),
		mFilter(GL_LINEAR),
		mMipmaps(false)
	{}

	texture_2d::~texture_2d() throw() {

	}

	GLenum texture_2d::get_target() const throw() {
		return mTarget;
	}

	GLint texture_2d::get_level() const throw() {
		return mLevel;
	}

	GLsizei texture_2d::get_width() const throw() {
		return mWidth;
	}

	GLsizei texture_2d::get_height() const throw() {
		return mHeight;
	}

	GLint texture_2d::get_border() const throw() {
		return mBorder;
	}

	GLenum texture_2d::get_format() const throw() {
		return mFormat;
	}

	GLenum texture_2d::get_type() const throw() {
		return mType;
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

	bool texture_2d::has_mipmaps() const throw() {
		return mMipmaps;
	}

	GLint texture_2d::get_internal_format() const throw() {
		return mInternalFormat;
	}

	void texture_2d::set_target(GLenum aValue) throw() {
		mTarget = aValue;
	}

	void texture_2d::set_level(GLint aValue) throw() {
		mLevel = aValue;
	}

	void texture_2d::set_border(GLint aValue) throw() {
		mBorder = aValue;
	}

	void texture_2d::set_format(GLenum aValue) throw() {
		mFormat = aValue;
	}

	void texture_2d::set_type(GLenum aValue) throw() {
		mType = aValue;
	}

	void texture_2d::set_border_colour(const vec4f& aValue) throw() {
		memcpy(&mBorderColour[0], &aValue[0], 4 * sizeof(GLfloat));
	}

	void texture_2d::set_filter(GLenum aValue) throw() {
		mFilter = aValue;
	}

	void texture_2d::set_mipmaps(bool aValue) throw() {
		mMipmaps = aValue;
	}

	void texture_2d::set_internal_format(GLint aValue) throw() {
		mInternalFormat = aValue;
	}

	void texture_2d::set_wrap(GLenum aValue) throw() {
		mWrap = aValue;
	}

	void texture_2d::create() {
		if(is_created()) destroy();
		glGenTextures(1, &mID);
		glBindTexture(mTarget, mID);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, mWrap);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, mWrap);
		if(mWrap == GL_CLAMP_TO_BORDER) glTexParameterfv(mTarget, GL_TEXTURE_BORDER_COLOR, &mBorderColour[0]);
		glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, mFilter);
		glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, mFilter);
		if(mMipmaps) glGenerateMipmap(mTarget);
		glBindTexture(mTarget, 0);
	}

	void texture_2d::destroy() {
		if(! is_created()) return;
		glDeleteTextures(1, &mID);
		mID = 0;
	}

	void texture_2d::bind() throw() {
		glBindTexture(mTarget, mID);
	}

	void texture_2d::load_raw(const void* aValue, GLsizei aWidth, GLsizei aHeight) throw() {
		mWidth = aWidth;
		mHeight = aHeight;
		glTexImage2D(mTarget, mLevel, mInternalFormat, aWidth, aHeight, mBorder, mFormat, mType, aValue);
	}

}}