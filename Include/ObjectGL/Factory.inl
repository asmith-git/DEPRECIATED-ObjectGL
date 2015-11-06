#ifndef OBJECT_GL_FACTORY_INL
#define OBJECT_GL_FACTORY_INL

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
	\file Factory.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <stdexcept>

namespace ObjectGL{
	
	// BaseFactory

	BaseFactory::BaseFactory() :
		mUsers(0)
	{

	}

	BaseFactory::~BaseFactory(){

	}

	void BaseFactory::Bind(){
		++mUsers;
		if(mUsers == 1) OnBind();
	}

	void BaseFactory::Unbind(){
		if(IsBound()) throw std::runtime_error("ObjectGL::Factory : Factory is not bound");
		--mUsers; 
		if(mUsers == 0) OnUnBind();
	}

	bool BaseFactory::IsBound() const{
		return mUsers > 0;
	}

}

#endif
