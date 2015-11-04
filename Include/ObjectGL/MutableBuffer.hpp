#ifndef OBJECT_GL_MUTABLE_BUFFER_HPP
#define OBJECT_GL_MUTABLE_BUFFER_HPP

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
	\file MutableBuffer.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

#include "Buffer.hpp"
#include "BufferFrequency.hpp"
#include "BufferUsage.hpp"

namespace ObjectGL{
	
	static /*constexpr*/ GLenum GetBufferHint(const BufferFrequency, const BufferUsage);

	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	template<const BufferFrequency FREQ, const BufferUsage USE>
	class MutableBuffer : public Buffer, public ReadWriteMapable{
	public:
		static const BufferFrequency Frequency = FREQ;
		static const BufferUsage Usage = USE;
	public:
		MutableBuffer(Context&);
		~MutableBuffer();

		void Clear();
		void Clear(const GLuint, const GLuint);

		void Copy(const BufferTarget, const GLuint, const GLuint, const GLuint);

		template<const BufferUsage U = USE>
		typename std::enable_if<U != BufferUsage::COPY, bool>::type IsMapped() const override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U != BufferUsage::COPY, void>::type Unmap() override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U != BufferUsage::COPY, void>::type Unmap(const GLuint, const GLuint) override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U == BufferUsage::READ, const void*>::type ReadMap() override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U == BufferUsage::READ, const void*>::type ReadMap(const GLuint, const GLuint) override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U == BufferUsage::DRAW, void*>::type WriteMap() override;

		template<const BufferUsage U = USE>
		typename std::enable_if<U == BufferUsage::DRAW, void*>::type WriteMap(const GLuint, const GLuint) override;

		// Inherited from Buffer
		void Allocate(const GLuint) override;
	};

	typedef MutableBuffer<BufferFrequency::STATIC, BufferUsage::DRAW> StaticDrawBuffer;
	typedef MutableBuffer<BufferFrequency::STATIC, BufferUsage::READ> StaticReadBuffer;
	typedef MutableBuffer<BufferFrequency::STATIC, BufferUsage::COPY> StaticCopyBuffer;

	typedef MutableBuffer<BufferFrequency::DYNAMIC, BufferUsage::DRAW> DynamicDrawBuffer;
	typedef MutableBuffer<BufferFrequency::DYNAMIC, BufferUsage::READ> DynamicReadBuffer;
	typedef MutableBuffer<BufferFrequency::DYNAMIC, BufferUsage::COPY> DynamicCopyBuffer;

	typedef MutableBuffer<BufferFrequency::STREAM, BufferUsage::DRAW> StreamDrawBuffer;
	typedef MutableBuffer<BufferFrequency::STREAM, BufferUsage::READ> StreamReadBuffer;
	typedef MutableBuffer<BufferFrequency::STREAM, BufferUsage::COPY> StreamCopyBuffer;

	template<const BufferUsage USE>
	using StaticBuffer = MutableBuffer<BufferFrequency::STATIC, USE>;

	template<const BufferUsage USE>
	using DynamicBuffer = MutableBuffer<BufferFrequency::DYNAMIC, USE>;

	template<const BufferUsage USE>
	using StreamBuffer = MutableBuffer<BufferFrequency::STREAM, USE>;

	template<const BufferFrequency FREQ>
	using DrawBuffer = MutableBuffer<FREQ, BufferUsage::DRAW>;

	template<const BufferFrequency FREQ>
	using ReadBuffer = MutableBuffer<FREQ, BufferUsage::READ>;

	template<const BufferFrequency FREQ>
	using StreamBuffer = MutableBuffer<FREQ, BufferUsage::STREAM>;

}

//#include "MutableBuffer.inl"

#endif
