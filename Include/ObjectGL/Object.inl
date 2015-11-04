#ifndef OBJECT_GL_OBJECT_INL
#define OBJECT_GL_OBJECT_INL

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

#include <stdexcept>

/*!
	\file Object.inl
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{
	
	// Object

	Object::Object(Context& aContext):
		mContext(aContext),
		mID(0)
	{}

	Object::~Object(){
		if(IsCreated()){
			Destroy();
		}
	}

	void Object::Create(){
		if(IsCreated()) throw std::runtime_error("ObjectGL::Object : Object has already been created");
	}

	void Object::Destroy(){
		if(! IsCreated()) throw std::runtime_error("ObjectGL::Object : Object has not been created");
	}

	bool Object::IsCreated() const{
		return mID != INVALID_ID;
	}

	Object::ID Object::GetID() const{
		return static_cast<ObjectID>(mID);
	}

	Context& Object::GetContext() const{
		return mContext;
	}

}

#endif
