#ifndef OBJECT_GL_OBJECT_HPP
#define OBJECT_GL_OBJECT_HPP

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : $objectgl_email
// GitHub repository : $objectgl_git

#include "Context.hpp"

/*!
	\file Object.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{

	class Context;
	
	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	class Object{
	public:
		enum ID : GLuint{
			INVALID_ID = 0
		};
	private:
		Context& mContext;
	protected:
		GLuint mID;
	private:
		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;
	public:
		Object(Context&);
		virtual ~Object();

		virtual void Create() = 0;
		virtual void Destroy() = 0;
		virtual bool IsCreated() const;

		ID GetID() const;

		Context& GetContext() const;
	};

}

#include "Object.inl"

#endif
