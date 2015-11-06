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

	enum class Storage : GLenum{
		NONE				= GL_NONE,
		UNSIGNED_NORMALISED	= GL_UNSIGNED_NORMALIZED,
		SIGNED_NORMALISED	= GL_SIGNED_NORMALIZED,
		UNSIGNED_INTEGRAL	= GL_UNSIGNED_INT,
		SIGNED_INTEGRAL		= GL_INT,
		FLOAT				= GL_FLOAT
	};

	template<const Storage TYPE>
	struct StorageType{
		typedef void Type;
		enum : GLuint{
			SizeBytes = 0,
			SizeBits = 0
		};
	};

	template<>
	struct StorageType<Storage::NONE>{
		typedef void Type;
		enum : GLuint{
			SizeBytes = 0,
			SizeBits = 0
		};
	};

	template<>
	struct StorageType<Storage::UNSIGNED_NORMALISED>{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_NORMALISED> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_NORMALISED> Type is not large enough to contain Size SizeBytes");
	};

	template<>
	struct StorageType<Storage::SIGNED_NORMALISED>{
		typedef int8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<SIGNED_NORMALISED> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<SIGNED_NORMALISED> Type is not large enough to contain Size SizeBytes");
	};

	template<>
	struct StorageType<Storage::UNSIGNED_INTEGRAL>{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_INTEGRAL> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_INTEGRAL> Type is not large enough to contain Size SizeBytes");
	};

	template<>
	struct StorageType<Storage::SIGNED_INTEGRAL>{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<SIGNED_INTEGRAL> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<SIGNED_INTEGRAL> Type is not large enough to contain Size SizeBytes");
	};

	template<>
	struct StorageType<Storage::FLOAT>{
		typedef float Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<FLOAT> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<FLOAT> Type is not large enough to contain Size SizeBytes");
	};

	template<const Storage TYPE>
	struct R{
		enum : GLuint{
			ElementCount = 1,
			FormatEnum = GL_RED,
			ElementSizeBits = StorageType<TYPE>::SizeBits,
			ElementSizeBytes = StorageType<TYPE>::SizeBytes,
			FormatSizeBits = ElementSizeBits * ElementCount,
			FormatSizeBytes = ElementSizeBytes * ElementCount,
			ElementEnum = static_cast<GLuint>(TYPE)
		};

		typedef BinaryData<FormatSizeBytes> FormatType;
		typedef typename StorageType<TYPE>::Type ElementType;

		static_assert(sizeof(FormatType) >= FormatSizeBytes, "ObjectGL::R FormatType is not large enough to contain FormatSize");
	};

	template<const Storage TYPE>
	struct RG{
		enum : GLuint{
			ElementCount = 2,
			FormatEnum = GL_RG,
			ElementSizeBits = StorageType<TYPE>::SizeBits,
			ElementSizeBytes = StorageType<TYPE>::SizeBytes,
			FormatSizeBits = ElementSizeBits * ElementCount,
			FormatSizeBytes = ElementSizeBytes * ElementCount,
			ElementEnum = static_cast<GLuint>(TYPE)
		};

		typedef BinaryData<FormatSizeBytes> FormatType;
		typedef typename StorageType<TYPE>::Type ElementType;

		static_assert(sizeof(FormatType) >= FormatSizeBytes, "ObjectGL::RG FormatType is not large enough to contain FormatSize");
	};

	template<const Storage TYPE>
	struct RGB{
		enum : GLuint{
			ElementCount = 3,
			FormatEnum = GL_RGB,
			ElementSizeBits = StorageType<TYPE>::SizeBits,
			ElementSizeBytes = StorageType<TYPE>::SizeBytes,
			FormatSizeBits = ElementSizeBits * ElementCount,
			FormatSizeBytes = ElementSizeBytes * ElementCount,
			ElementEnum = static_cast<GLuint>(TYPE)
		};

		typedef BinaryData<FormatSizeBytes> FormatType;
		typedef typename StorageType<TYPE>::Type ElementType;

		static_assert(sizeof(FormatType) >= FormatSizeBytes, "ObjectGL::RGB FormatType is not large enough to contain FormatSize");
	};

	template<const Storage TYPE>
	struct RGBA{
		enum : GLuint{
			ElementCount = 4,
			FormatEnum = GL_RGBA,
			ElementSizeBits = StorageType<TYPE>::SizeBits,
			ElementSizeBytes = StorageType<TYPE>::SizeBytes,
			FormatSizeBits = ElementSizeBits * ElementCount,
			FormatSizeBytes = ElementSizeBytes * ElementCount,
			ElementEnum = static_cast<GLuint>(TYPE)
		};

		typedef BinaryData<FormatSizeBytes> FormatType;
		typedef typename StorageType<TYPE>::Type ElementType;

		static_assert(sizeof(FormatType) * 8 >= FormatSizeBytes, "ObjectGL::RGBA FormatType is not large enough to contain FormatSize");
	};
}}

#endif
