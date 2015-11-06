#ifndef OBJECT_GL_COLOUR_FORMAT_HPP
#define OBJECT_GL_COLOUR_FORMAT_HPP

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
	\file ColourFormat.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <cstdint>
#include "ObjectGLInit.inl"

namespace ObjectGL { namespace ColourFormat{

	namespace Implementation{

		template<const GLuint BITS>
		static void CopyBits(const void* aSrc, const GLuint aSrcOffset, void* aDst, const GLuint aDstOffset){
			//! \todo Optimise

			const bool byteAligned = ! ((BITS & 7) || (aSrcOffset & 7) || (aDstOffset & 7));

			if(byteAligned){
				std::memcpy(
					static_cast<const uint8_t*>(aSrc) + (aSrcOffset / 8), 
					static_cast<uint8_t*>(aDst) + (aDstOffset / 8),
					BITS / 8
				);
			}else{
				const uint8_t* const src = static_cast<const uint8_t*>(aSrc);
				uint8_t* const dst = static_cast<uint8_t*>(aDst);

				GLuint srcOffset = aSrcOffset;
				GLuint dstOffset = aDstOffset;
				for(GLuint i = 0; i != BITS; ++i){
					const uint8_t srcByte = src[srcOffset / 8];
					uint8_t& dstByte = dst[dstOffset / 8];

					const uint8_t srcMask = 1 << (aSrcOffset & 7);
					const uint8_t dstMask = 1 << (dstOffset & 7);

					uint8_t bit = srcByte & srcMask;

					dstByte &= ~dstMask;
					if(bit) dstByte |= dstMask;

					++srcOffset;
					++dstOffset;
				}
			}
		}
	}

	template<class Format>
	static typename Format::Type Read(const void* const aData, const GLuint aOffset){
		typename Format::Type tmp = 0;
		return Implementation::CopyBits<Format::BitDepth>(aData, aOffset * Format::BitDepth, &tmp, 0);
		return tmp;
	}

	template<class Format>
	static void Write(void* const aData, const GLuint aOffset, const typename Format::Type aValue){
		return Implementation::CopyBits<Format::BitDepth>(&aValue, 0, aData, aOffset * Format::BitDepth);
	}

	struct R{
		enum : GLuint{
			BitDepth = 8
		};

		typedef uint8_t Type;

		static_assert(sizeof(Type) * 8 >= BitDepth, "ObjectGL::R Type is not large enough to contain BitDepth");
	};

	struct RG{
		enum : GLuint{
			BitDepth = 16
		};

		typedef uint16_t Type;

		static_assert(sizeof(Type) * 8 >= BitDepth, "ObjectGL::RG Type is not large enough to contain BitDepth");
	};

	struct RGB{
		enum : GLuint{
			BitDepth = 24
		};

		typedef uint32_t Type;

		static_assert(sizeof(Type) * 8 >= BitDepth, "ObjectGL::RGB Type is not large enough to contain BitDepth");
	};

	struct RGBA{
		enum : GLuint{
			BitDepth = 32
		};

		typedef uint32_t Type;

		static_assert(sizeof(Type) * 8 >= BitDepth, "ObjectGL::RGBA Type is not large enough to contain BitDepth");
	};
}}

#endif
