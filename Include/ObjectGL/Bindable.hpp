#ifndef OBJECT_GL_BINDABLE_HPP
#define OBJECT_GL_BINDABLE_HPP

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
	\file Bindable.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL{

	/*!
		\brief
		\author Adam Smith
		\date 6th November 2015
		\version 1.0
	*/
	template<class ...PARAMS>
	class Bindable{
	public:
		virtual ~Bindable(){}

		virtual void Bind(PARAMS...) = 0;
		virtual void Unbind(PARAMS...) = 0;
		virtual bool IsBound(PARAMS...) const = 0;
	};

	/*!
		\brief
		\author Adam Smith
		\date 6th November 2015
		\version 1.0
	*/
	template<class ...PARAMS>
	class BindGuard{
	private:
		Bindable<PARAMS>& mBindable;
		PARAMS mParams;
	public:
		BindGuard(Bindable<PARAMS>& aBindable, PARAMS... aParams) :
			mBindable(aBindable),
			mParams(aParams)
		{
			mBindable.Bind(mParams);
		}

		~BindGuard(){
			mBindable.Unbind(mParams);
		}
	};

}

#endif
