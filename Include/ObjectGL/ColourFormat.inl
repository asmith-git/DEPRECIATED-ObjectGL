#ifndef OBJECT_GL_COLOUR_FORMAT_INL
#define OBJECT_GL_COLOUR_FORMAT_INL

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
	\file ColourFormat.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL { namespace ColourFormat{

	template<class STORAGE>
	struct StorageEnums<STORAGE, 1>{
		enum : GLenum{
			Enum = GL_RED
		};
	};

	template<class STORAGE>
	struct StorageEnums<STORAGE, 2>{
		enum : GLenum{
			Enum = GL_RG
		};
	};

	template<class STORAGE>
	struct StorageEnums<STORAGE, 3>{
		enum : GLenum{
			Enum = GL_RGB
		};
	};

	template<class STORAGE>
	struct StorageEnums<STORAGE, 4>{
		enum : GLenum{
			Enum = GL_RGBA
		};
	};

}}

#endif
