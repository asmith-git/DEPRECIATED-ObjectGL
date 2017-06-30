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
	{
		glGenVertexArrays(1, &mID);
		if (mID == object::INVALID_ID) throw std::runtime_error("asmith::gl::vertex_array::create : glGenVertexArrays returned 0");
	}

	vertex_array::~vertex_array() {
		if(mID == 0) return;
		glDeleteVertexArrays(1, &mID);
		mID = 0;
	}

	GLuint vertex_array::add_attribute(std::shared_ptr<vertex_buffer> aBuffer, const vertex_attribute& aAttribute) {
		mAttributes.push_back(aAttribute);
		mBuffers.push_back(aBuffer);

		const GLuint attrib = mAttributes.size() - 1;

		const std::shared_ptr<vertex_buffer> previous = vertex_buffer::get_buffer_bound_to(mContext, GL_ARRAY_BUFFER);
		if (previous && previous->is_mapped())  throw std::runtime_error("asmith::gl::vertex_array::add_attribute : VBO currently bound to GL_ARRAY_BUFFER is mapped");

		glBindVertexArray(mID);
		const vertex_attribute& a = mAttributes[attrib];
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[attrib]->get_id());
		glVertexAttribPointer(attrib, a.size, a.type, a.normalised, a.stride, a.pointer);
		glBindBuffer(GL_ARRAY_BUFFER, previous ? previous->get_id() : 0);
		glBindVertexArray(0);

		return attrib;
	}

	void vertex_array::draw_arrays(GLenum aMode, GLint aFirst, GLsizei aCount) const throw() {
		if(mID == 0) return;
		glBindVertexArray(mID);
		const GLuint  s = mAttributes.size();
		for(GLuint  i = 0; i < s; ++i) glEnableVertexAttribArray(i);
		glDrawArrays(aMode, aFirst, aCount);
		for(GLuint  i = 0; i < s; ++i) glDisableVertexAttribArray(i);
		glBindVertexArray(0);
	}

}}