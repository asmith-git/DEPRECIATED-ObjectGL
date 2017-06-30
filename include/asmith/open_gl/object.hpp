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

#ifndef ASMITH_OPENGL_OBJECT_HPP
#define ASMITH_OPENGL_OBJECT_HPP

#include <memory>
#include "context.hpp"

namespace asmith { namespace gl {
	
	/*!
		\brief Base class for OpenGL objects
		\author Adam Smith
		\date Created : 4th November 2015 Modified 30th June 2017
		\version 2.2
	*/
	class object : public std::enable_shared_from_this<object> {
	public:
		enum id_t : GLuint {
			INVALID_ID = 0
		};
	protected:
		context& mContext;
		GLuint mID;
	private:
		object(const object&) = delete;
		object(object&&) = delete;
		object& operator=(const object&) = delete;
		object& operator=(object&&) = delete;
	public:
		static std::shared_ptr<object> get_object_with_id(id_t) throw();

		object(context&);
		virtual ~object();

		context& get_context() const throw();

		virtual void create() = 0;
		virtual void destroy() = 0;
		virtual bool is_created() const throw();

		id_t get_id() const throw();
		operator bool() const throw();
	};

}}

#endif