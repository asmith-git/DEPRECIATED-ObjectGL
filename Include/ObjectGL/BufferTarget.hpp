#ifndef OBJECT_GL_BUFFER_TARGET_HPP
#define OBJECT_GL_BUFFER_TARGET_HPP

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
	\file BufferTarget.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{

	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	enum class BufferTarget : GLenum{
		ARRAY				= GL_ARRAY_BUFFER,
		ATOMIC_COUNTER		= GL_ATOMIC_COUNTER_BUFFER,
		COPY_READ			= GL_COPY_READ_BUFFER,
		COPY_WRITE			= GL_COPY_WRITE_BUFFER,
		DRAW_INDIRECT		= GL_DRAW_INDIRECT_BUFFER,
		DISPATCH_INDIRECT	= GL_DISPATCH_INDIRECT_BUFFER,
		ELEMENT_ARRAY		= GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK			= GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK		= GL_PIXEL_UNPACK_BUFFER,
		QUERY				= GL_QUERY_BUFFER,
		SHADER_STORAGE		= GL_SHADER_STORAGE_BUFFER,
		TEXTURE				= GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK	= GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM				= GL_UNIFORM_BUFFER
	};
}

#endif
