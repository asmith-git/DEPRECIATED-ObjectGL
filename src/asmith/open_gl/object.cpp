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

#include <vector>
#include "asmith/open_gl/object.hpp"

namespace asmith { namespace gl {
	
	// object

	static std::vector<object*> OBJECT_LIST;

	std::shared_ptr<object> object::get_object_with_id(id_t aID) throw() {
		for(object* i : OBJECT_LIST) {
			if(i->get_id() == aID) return i->shared_from_this();
		}
		return std::shared_ptr<object>();
	}
	
	object::object(context& aContext) :
		mContext(aContext),
		mID(INVALID_ID)
	{
		OBJECT_LIST.push_back(this);
	}
	
	object::~object() {
		// if(is_created()) destroy();
		OBJECT_LIST.erase(std::find(OBJECT_LIST.begin(), OBJECT_LIST.end(), this));
	}

	context& object::get_context() const throw() {
		return mContext;
	}
	
	object::id_t object::get_id() const throw() {
		return static_cast<id_t>(mID);
	}

	bool object::is_created() const throw() {
		return mID != INVALID_ID;
	}
	
	object::operator bool() const throw() {
		return is_created();
	}

}}