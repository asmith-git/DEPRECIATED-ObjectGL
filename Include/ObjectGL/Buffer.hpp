#ifndef OBJECT_GL_BUFFER_HPP
#define OBJECT_GL_BUFFER_HPP

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

/*!
	\file Buffer.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

#include "Object.hpp"
#include "Bindable.hpp"
#include "BufferTarget.hpp"

namespace ObjectGL{

	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	class Buffer : public Object, public Bindable<const BufferTarget>{
	protected:
		GLuint mSize;
	protected:
		// Inherited from Object

		virtual void OnContextCreated() override;
	public:
		Buffer(Context&);
		virtual ~Buffer();

		GLuint Size() const;

		virtual void Allocate(const GLuint) = 0;

		// Inherited from Bindable

		void Bind(const BufferTarget) override;
		void Unbind(const BufferTarget) override;
		bool IsBound(const BufferTarget) const override;

		// Inherited from Object

		virtual void Create() override;
		virtual void Destroy() override;
	};

	//typedef BindGuard<const BufferTarget> BufferGuard;

}

#include "Buffer.inl"

#endif
