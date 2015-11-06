#ifndef OBJECT_GL_PROGRAM_HPP
#define OBJECT_GL_PROGRAM_HPP

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

#include <vector>
#include "Bindable.hpp"
#include "Shader.hpp"

/*!
	\file Program.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL{

	//! \todo Program vertex shader inputs
	//! \todo Program fragment shader outputs
	//! \todo Program transform feedpack
	//! \todo Program speration

	/*!
		\brief
		\author Adam Smith
		\date 6th November 2015
		\version 1.0
	*/
	class Program : public Object, public Bindable<void>{
	public:
		typedef BindGuard<void> Guard;
	private:
		std::vector<Shader*> mShaders;
	public:
		Program(Context&);
		~Program();

		void Attach(Shader&);

		// Inherited from Bindable
		void Bind() override;
		void Unbind() override;
		bool IsBound() const override;

		// Inherited from Object

		void Create() override;
		void Destroy() override;
	};

}

#include "Program.inl"

#endif
