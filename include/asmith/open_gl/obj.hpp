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

#ifndef ASMITH_OPENGL_OBJ_HPP
#define ASMITH_OPENGL_OBJ_HPP

#include <iostream>
#include <vector>
#include "vertex_array.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief 
		\author Adam Smith
		\date Created : ? Modified 29th June 2017
		\version 3.0
	*/
	struct obj {
		struct face {
			GLuint vertex;
			GLuint texture_coordinate;
			GLuint normal;
		};

		struct triangle {
			face points[3];
		};
		
		std::vector<vec3f> vertices;
		std::vector<vec3f> normals;
		std::vector<vec2f> texture_coordinates;
		std::vector<triangle> faces;

		void load(std::istream&);
		std::shared_ptr<vertex_array> create_vao() const;
	};
}}

#endif