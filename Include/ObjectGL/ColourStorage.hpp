#ifndef OBJECT_GL_COLOUR_STORAGE_HPP
#define OBJECT_GL_COLOUR_STORAGE_HPP

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
	\file ColourStorage.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <cstdint>
#include "ObjectGLInit.inl"
#include "BinaryData.hpp"

namespace ObjectGL { namespace ColourFormat{


	struct StorageVoid{
		typedef void Type;
		enum : GLuint{
			SizeBytes = 0,
			SizeBits = 0,
			Enum = GL_NONE
		};
	}; 
	
	struct StorageUnsignedNormalised{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8,
			Enum = GL_UNSIGNED_NORMALIZED
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_NORMALISED> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_NORMALISED> Type is not large enough to contain Size SizeBytes");
	};

	struct StorageSignedNormalised{
		typedef int8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8,
			Enum = GL_SIGNED_NORMALIZED
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<SIGNED_NORMALISED> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<SIGNED_NORMALISED> Type is not large enough to contain Size SizeBytes");
	};

	struct StorageUnsignedIntegral{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8,
			Enum = GL_UNSIGNED_INT
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_INTEGRAL> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<UNSIGNED_INTEGRAL> Type is not large enough to contain Size SizeBytes");
	};

	struct StorageSignedIntegral{
		typedef uint8_t Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8,
			Enum = GL_INT
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<SIGNED_INTEGRAL> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<SIGNED_INTEGRAL> Type is not large enough to contain Size SizeBytes");
	};

	struct StorageFloat{
		typedef float Type;
		enum : GLuint{
			SizeBytes = sizeof(Type),
			SizeBits = SizeBytes * 8,
			Enum = GL_FLOAT
		};

		static_assert(SizeBytes * 8 >= SizeBytes, "ObjectGL::StorageType<FLOAT> SizeBits is larger than SizeBytes");
		static_assert(sizeof(Type) >= SizeBytes, "ObjectGL::StorageType<FLOAT> Type is not large enough to contain Size SizeBytes");
	};
}}


#endif
