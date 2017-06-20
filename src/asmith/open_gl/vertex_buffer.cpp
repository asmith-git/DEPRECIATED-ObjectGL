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

#include <stdexcept>
#include "asmith/open_gl/vertex_buffer.hpp"

namespace asmith { namespace gl {
	
	// vertex_buffer
	vertex_buffer::vertex_buffer() :
		mTarget(GL_INVALID_ENUM),
		mSize(0),
		mUsage(GL_INVALID_ENUM)
	{}

	vertex_buffer::vertex_buffer(GLenum aUsage) :
		mTarget(GL_INVALID_ENUM),
		mSize(0),
		mUsage(aUsage)
	{}

	vertex_buffer::~vertex_buffer() {

	}

	GLsizeiptr vertex_buffer::size() const throw() {
		return mSize;
	}

	bool vertex_buffer::set_usage(GLenum aUsage) throw() {
		if(is_created()) return false;
		mUsage = aUsage;
		return true;
	}

	GLenum vertex_buffer::get_usage() const throw() {
		return mUsage;
	}

	void vertex_buffer::set_data(const GLvoid* aData, GLsizeiptr aSize) {
		if(! is_created()) throw std::runtime_error("asmith::gl::vertex_buffer::set_data : Buffer does not exist");
		if(mUsage == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::vertex_buffer::set_data : Usage not set");
		if(mTarget == GL_INVALID_ENUM) throw std::runtime_error("asmith::gl::vertex_buffer::set_data : Buffer is not bound");
		mSize = aSize;
#if ASMITH_GL_VERSION_LE(2, 1)		
		glBufferDataARB(mTarget, aSize, aData, mUsage);
#else
		glBufferData(mTarget, aSize, aData, mUsage);
#endif
	}

	bool vertex_buffer::bind(GLenum aTarget) throw() {
#if ASMITH_GL_VERSION_LE(2,1)
		glBindBufferARB(aTarget, mID);
#else
		glBindBuffer(aTarget, mID);
#endif
		return true;
	}

	bool vertex_buffer::unbind(GLenum aTarget) throw() {
		if(mTarget == GL_INVALID_ENUM) return false;
		mTarget = GL_INVALID_ENUM;
		//! \todo Implement
		return true;
	}

	void vertex_buffer::create() {
		if(is_created()) destroy();

#if ASMITH_GL_VERSION_LE(2,1)
		glGenBuffersARB(1, &mID);
#else
		glGenBuffers(1, &mID);
#endif
		mSize = 0;
		if(mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::vertex_buffer::create : glGenBuffers returned 0");
	}

	void vertex_buffer::destroy() {
		if(! is_created()) return;
#if ASMITH_GL_VERSION_LE(2,1)
		glDeleteBuffersARB(1, &mID);
#else
		glDeleteBuffers(1, &mID);
#endif
		mID = 0;
		mSize = 0;
	}

}}