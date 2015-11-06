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
	\file BufferMutable.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

#include "Buffer.hpp"

namespace ObjectGL{
	
	static /*constexpr*/ GLenum GetBufferHint(const Buffer::Frequency, const Buffer::Usage);

	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	template<const Buffer::Frequency FREQ, const Buffer::Usage USE>
	class MutableBuffer : public Buffer, public ReadWriteMapable{
	public:
		static const Buffer::Frequency Frequency = FREQ;
		static const Buffer::Usage Usage = USE;
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

	typedef MutableBuffer<Buffer::Frequency::STATIC, Buffer::Usage::DRAW> StaticDrawBuffer;
	typedef MutableBuffer<Buffer::Frequency::STATIC, Buffer::Usage::READ> StaticReadBuffer;
	typedef MutableBuffer<Buffer::Frequency::STATIC, Buffer::Usage::COPY> StaticCopyBuffer;

	typedef MutableBuffer<Buffer::Frequency::DYNAMIC, Buffer::Usage::DRAW> DynamicDrawBuffer;
	typedef MutableBuffer<Buffer::Frequency::DYNAMIC, Buffer::Usage::READ> DynamicReadBuffer;
	typedef MutableBuffer<Buffer::Frequency::DYNAMIC, Buffer::Usage::COPY> DynamicCopyBuffer;

	typedef MutableBuffer<Buffer::Frequency::STREAM, Buffer::Usage::DRAW> StreamDrawBuffer;
	typedef MutableBuffer<Buffer::Frequency::STREAM, Buffer::Usage::READ> StreamReadBuffer;
	typedef MutableBuffer<Buffer::Frequency::STREAM, Buffer::Usage::COPY> StreamCopyBuffer;

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
