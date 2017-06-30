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
#include "asmith/open_gl/context_state.hpp"

namespace asmith { namespace gl {
	
	// object

	std::shared_ptr<object> object::get_object_with_id(context& aContext, id_t aID) throw() {
		for(object* i : aContext.state->object_list) {
			if(i->get_id() == aID) return i->shared_from_this();
		}
		return std::shared_ptr<object>();
	}

	object::object(context& aContext) :
		mContext(aContext),
		mID(INVALID_ID)
	{
		mContext.state->object_list.push_back(this);
	}
	
	object::~object() {
		// if(is_created()) destroy();
		mContext.state->object_list.erase(std::find(mContext.state->object_list.begin(), mContext.state->object_list.end(), this));
	}

	context& object::get_context() const throw() {
		return mContext;
	}
	
	object::id_t object::get_id() const throw() {
		return static_cast<id_t>(mID);
	}

}}