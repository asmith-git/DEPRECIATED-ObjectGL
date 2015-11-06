#ifndef OBJECT_GL_BINARY_DATA_HPP
#define OBJECT_GL_BINARY_DATA_HPP

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
	\file BinaryData.hpp
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <cstdint>

namespace ObjectGL {

	namespace BinaryDataImplementation{

		template<const uint32_t BYTES>
		class Large{
		private:
			uint8_t mBytes[BYTES];
		public:
			Large(const uint8_t aBytes){
				for (uint8_t& byte : mBytes) byte = aByte;
			}
		};

		template<const uint32_t BYTES>
		struct Container{
			typedef Large<BYTES> Type;
		};

		template<>
		struct Container<0>{
			typedef void Type;
		};

		template<>
		struct Container<1>{
			typedef uint8_t Type;
		};

		template<>
		struct Container<2>{
			typedef uint16_t Type;
		};

		template<>
		struct Container<3>{
			typedef uint32_t Type;
		};

		template<>
		struct Container<4>{
			typedef uint32_t Type;
		};

		template<>
		struct Container<5>{
			typedef uint64_t Type;
		};

		template<>
		struct Container<6>{
			typedef uint64_t Type;
		};

		template<>
		struct Container<7>{
			typedef uint64_t Type;
		};

		template<>
		struct Container<8>{
			typedef uint64_t Type;
		};
	}


	template<const uint32_t BYTES>
	using BinaryData = typename BinaryDataImplementation::Container<BYTES>::Type;
}

#endif
