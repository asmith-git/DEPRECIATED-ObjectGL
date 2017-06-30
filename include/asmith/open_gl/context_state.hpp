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

#ifndef ASMITH_OPENGL_CONTEXT_STATE_HPP
#define ASMITH_OPENGL_CONTEXT_STATE_HPP

#include "program.hpp"
#include "vertex_buffer.hpp"
#include "light.hpp"

namespace asmith { namespace gl { namespace implementation {
	
	/*!
		\brief
		\author Adam Smith
		\date Created : 30th June 2017 Modified 30th June 2017
		\version 1.0
	*/
	struct context_state {
		std::vector<object*> object_list;
		std::shared_ptr<program> currently_bound_program;
		std::weak_ptr<vertex_buffer> currently_bound_vbos[14];
		std::shared_ptr<light> lights[GL_MAX_LIGHTS];
		vec4f ambient_scene_colour;
		bool lighting_enabled;

		context_state();
	};

}}}

#endif