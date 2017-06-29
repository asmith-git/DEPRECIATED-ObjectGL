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

#include "asmith/open_gl/material.hpp"

namespace asmith { namespace gl {
	
	// material

	material::material() throw() :
		ambient(1.f, 1.f, 1.f, 1.f),
		diffuse(1.f, 1.f, 1.f, 1.f),
		specular(1.f, 1.f, 1.f, 1.f),
		emission(),
		shineiness(20.f)
	{}

	void material::use(GLenum aFace) const throw() {
		glMaterialfv(aFace, GL_AMBIENT, &ambient[0]);
		glMaterialfv(aFace, GL_DIFFUSE, &diffuse[0]);
		glMaterialfv(aFace, GL_SPECULAR, &specular[0]);
		glMaterialfv(aFace, GL_EMISSION, &emission[0]);
		glMaterialf(aFace, GL_SHININESS, shineiness);
	}

	void material::use_front() const throw() {
		use(GL_FRONT);
	}

	void material::use_back() const throw() {
		use(GL_BACK);
	}

	void material::use_front_and_back() const throw() {
		use(GL_FRONT_AND_BACK);
	}

}}