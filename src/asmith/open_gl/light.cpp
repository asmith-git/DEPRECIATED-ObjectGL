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

#include "asmith/open_gl/light.hpp"

namespace asmith { namespace gl {

	static std::shared_ptr<light> LIGHTS[GL_MAX_LIGHTS];
	
	// light

	std::shared_ptr<light> light::get_light(GLenum aID) throw() {
		if(aID < GL_LIGHT0 || aID >= (GL_LIGHT0 + GL_MAX_LIGHTS)) return std::shared_ptr<light>();
		if(! LIGHTS[aID]) LIGHTS[aID].reset(new light(aID));
		return LIGHTS[aID];
	}


	light::light(GLenum aID) :
		mID(aID),
		mEnabled(false)
	{}

	light::~light() {

	}

	void light::enable() throw() {
		if(mEnabled) return;
		glEnable(mID);
		mEnabled = true;
	}

	void light::disable() throw() {
		if(! mEnabled) return;
		glDisable(mID);
		mEnabled = false;
	}

	bool light::is_enabled() const throw() {
		return mEnabled;
	}



}}