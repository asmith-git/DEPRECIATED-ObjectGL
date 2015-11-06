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
#include "BinaryData.hpp"
#include "ColourStorage.hpp"

namespace ObjectGL { namespace ColourFormat{

	namespace Implementation{

		template<const GLuint BITS>
		static void CopyBits(const void* aSrc, const GLuint aSrcOffset, void* aDst, const GLuint aDstOffset){

			const bool byteAligned = ! ((BITS & 7) || (aSrcOffset & 7) || (aDstOffset & 7));

			if(byteAligned){
				std::memcpy(
					static_cast<const uint8_t*>(aSrc) + (aSrcOffset / 8), 
					static_cast<uint8_t*>(aDst) + (aDstOffset / 8),
					BITS / 8
				);
			}else{
				//! \todo Optimise
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

	template<class STORAGE, const GLuint ELEMENTS>
	struct StorageEnums;

	template<class STORAGE, const GLuint ELEMENTS>
	struct ColourFormat{
		enum : GLuint{
			ElementCount = ELEMENTS,
			FormatEnum = StorageEnums<STORAGE, ELEMENTS>::Enum,
			ElementSizeBits = STORAGE::SizeBits,
			ElementSizeBytes = STORAGE::SizeBytes,
			ElementEnum = STORAGE::Enum,
			FormatSizeBits = ElementSizeBits * ElementCount,
			FormatSizeBytes = ElementSizeBytes * ElementCount
		};

		typedef typename STORAGE::Type ElementType;
		typedef BinaryData<FormatSizeBytes> FormatType;

		static_assert(sizeof(FormatType) >= FormatSizeBytes, "ObjectGL::ColourFormat FormatType is not large enough to contain FormatSize");

		static FormatType Read(const void* const aData, const GLuint aOffset){
			typename FormatType tmp = 0;
			return Implementation::CopyBits<Format::FormatSizeBits>(aData, aOffset * Format::FormatSizeBits, &tmp, 0);
			return tmp;
		}

		static void Write(void* const aData, const GLuint aOffset, const typename FormatType aValue){
			return Implementation::CopyBits<Format::FormatSizeBits>(&aValue, 0, aData, aOffset * Format::FormatSizeBits);
		}
	};
}}

#include "ColourFormat.inl"

#endif
