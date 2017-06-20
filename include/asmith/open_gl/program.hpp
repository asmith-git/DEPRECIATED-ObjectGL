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

#ifndef ASMITH_OPENGL_PROGRAM_HPP
#define ASMITH_OPENGL_PROGRAM_HPP

#include <vector>
#include "shader.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief OpenGL program
		\author Adam Smith
		\date Created : 6th November 2015 Modified 19th Jube 2017
		\version 2.0
	*/
	class program : public object {
	public:
		enum id_t : GLuint{
			INVALID_ID = 0
		};
	private:
		std::vector<std::shared_ptr<shader>> mShaders;
	public:
		~program();

		void attach(std::shared_ptr<shader>);
		void detach(std::shared_ptr<shader>);
		size_t shader_count() const throw();
		std::shared_ptr<shader> get_shader(size_t) const throw();
		
		void bind();
		void unbind();
		bool is_bound() const throw();
		bool is_currently_bound() const throw();
		
		// Inherited from object
		void create() override;
		void destroy() override;
	};

	static std::shared_ptr<program> link_program(const std::vector<std::shared_ptr<shader>>& aShaders) {
		std::shared_ptr<program> tmp(new program());
		for(const std::shared_ptr<shader>& i : aShaders) tmp->attach(i);
		tmp->create();
		return tmp;
	}
}}

#endif
