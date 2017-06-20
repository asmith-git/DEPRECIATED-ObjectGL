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

#include "asmith/open_gl/vertex_buffer.hpp"

namespace asmith { namespace gl {
	
	// vertex_buffer
	vertex_buffer::vertex_buffer() :
		mTarget(GL_INVALID_ENUM),
		mData(nullptr),
		mSize(0),
		mUsage(GL_INVALID_ENUM)
	{}

	vertex_buffer::vertex_buffer(GLenum aUsage) :
		mTarget(GL_INVALID_ENUM),
		mData(nullptr),
		mSize(0),
		mUsage(aUsage)
	{}

	vertex_buffer::~vertex_buffer() {

	}

	bool vertex_buffer::set_usage(GLenum aUsage) throw() {
		if(is_created()) return false;
		return false;
	}

	GLenum vertex_buffer::get_usage() const throw() {
		return mUsage;
	}

	void vertex_buffer::set_data(const GLvoid* aData, GLsizeiptr aSize) {
		mData = aData;
		mSize = aSize;
	}

	bool vertex_buffer::bind(GLenum aTarget) throw() {
		return false;
	}

	bool vertex_buffer::unbind(GLenum aTarget) throw() {
		return false;
	}

	void vertex_buffer::create() {

	}

	void vertex_buffer::destroy() {

	}

}}