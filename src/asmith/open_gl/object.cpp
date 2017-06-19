//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#include "asmith/open_gl/object.hpp"

namespace asmith { namespace gl {
	
	// class object
	
	object::object() :
		mID(INVALID_ID)
	{}
	
	object::~object() {
		if(is_created()) destroy();
	}
	
	id_t object::get_id() const throw() {
		return static_cast<id_t>(mID);
	}
	
	operator object::bool() const throw() {
		return mID != INVALID_ID;
	}

}}

#endif