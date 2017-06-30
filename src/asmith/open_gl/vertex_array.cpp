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

#include "asmith/open_gl/vertex_array.hpp"

namespace asmith { namespace gl {
	
	// class vertex_array
	
	vertex_array::vertex_array(context& aContext) :
		object(aContext)
	{}

	vertex_array::~vertex_array() {

	}

	GLuint vertex_array::add_attribute(std::shared_ptr<vertex_buffer> aBuffer, const vertex_attribute& aAttribute) {
		mAttributes.push_back(aAttribute);
		mBuffers.push_back(aBuffer);
		return mAttributes.size() - 1;
	}

	void vertex_array::create() {
		if (is_created()) destroy();

		glGenVertexArrays(1, &mID);
		if(mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::vertex_array::create : glGenVertexArrays returned 0");

		const GLuint  s = mAttributes.size();
		if(s > 0) {
			const std::shared_ptr<vertex_buffer> previous = vertex_buffer::get_buffer_bound_to(GL_ARRAY_BUFFER);
			if(previous && previous->is_mapped())  throw std::runtime_error("asmith::gl::vertex_array::create : VBO currently bound to GL_ARRAY_BUFFER is mapped");

			glBindVertexArray(mID);
			for(GLuint  i = 0; i < s; ++i) {
				const vertex_attribute& a = mAttributes[i];
				glBindBuffer(GL_ARRAY_BUFFER, mBuffers[i]->get_id());
				glVertexAttribPointer(i, a.size, a.type, a.normalised, a.stride, a.pointer);
			}
			glBindBuffer(GL_ARRAY_BUFFER, previous ? previous->get_id() : 0);
			glBindVertexArray(0);
		}
	}

	void vertex_array::destroy() {
		if(! is_created()) return;
		glDeleteVertexArrays(1, &mID);
		mID = 0;
	}


	void vertex_array::draw_arrays(GLenum aMode, GLint aFirst, GLsizei aCount) const throw() {
		if(! is_created()) return;
		glBindVertexArray(mID);
		const GLuint  s = mAttributes.size();
		for(GLuint  i = 0; i < s; ++i) glEnableVertexAttribArray(i);
		glDrawArrays(aMode, aFirst, aCount);
		for(GLuint  i = 0; i < s; ++i) glDisableVertexAttribArray(i);
		glBindVertexArray(0);
	}

}}