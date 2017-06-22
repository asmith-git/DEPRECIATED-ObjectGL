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

#ifndef ASMITH_OPENGL_VERTEX_ARRAY_HPP
#define ASMITH_OPENGL_VERTEX_ARRAY_HPP

#include <vector>
#include "vertex_buffer.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief Base class for OpenGL vertex array objects (VAO)
		\author Adam Smith
		\date Created : 22nd June 2017 Modified 22nd June 2017
		\version 1.0
	*/
	class vertex_array : public object {
	public:
		struct vertex_attribute {
			GLint size;
			GLenum type;
			GLboolean normalised;
			GLsizei stride;
			const GLvoid* pointer;
		};
	private:
		std::vector<vertex_attribute> mAttributes;
		std::vector<std::shared_ptr<vertex_buffer>> mBuffers;
	public:
		vertex_array();
		~vertex_array();

		GLuint add_attribute(std::shared_ptr<vertex_buffer>, const vertex_attribute&);

		// Inherited from object 
		
		void create() override;
		void destroy() override;
	};
}}

#endif