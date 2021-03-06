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

#ifndef ASMITH_OPENGL_VERTEX_BUFFER_HPP
#define ASMITH_OPENGL_VERTEX_BUFFER_HPP

#include "object.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief Base class for OpenGL shader objects
		\author Adam Smith
		\date Created : 4th November 2015 Modified 30th June 2017
		\version 2.4
	*/
	class vertex_buffer : public object {
	private:
		std::weak_ptr<vertex_buffer> mPreviousBinding;
		GLenum mTarget;
		GLsizeiptr mSize;
		GLenum mUsage;
		bool mIsMapped;
	public:
		static std::shared_ptr<vertex_buffer> get_buffer_bound_to(context&, GLenum) throw();

		vertex_buffer(context&);
		vertex_buffer(context&, GLenum);
		~vertex_buffer();

		void buffer(const GLvoid*, GLsizeiptr);
		void sub_buffer(GLintptr, const GLvoid*, GLsizeiptr);
		void get_buffer(GLintptr, GLvoid*, GLsizeiptr);
#if ASMITH_GL_VERSION_GE(4, 4)	
		void buffer_storage(const GLvoid*, GLsizeiptr);
#endif
		bool set_usage(GLenum) throw();
		GLenum get_usage() const throw();

		bool bind(GLenum) throw();
		bool unbind() throw();
		bool is_currently_bound() const throw();
		bool is_bound() const throw();
		GLenum get_bind_target() const throw();

		GLsizeiptr size() const throw();

#if ASMITH_GL_VERSION_GE(3, 0)	
		GLvoid* map(GLenum) throw();
		GLvoid* map_range(GLsizeiptr, GLsizeiptr, GLenum) throw();
		bool unmap() throw();
		bool is_mapped() const throw();
#endif
	};
}}

#endif