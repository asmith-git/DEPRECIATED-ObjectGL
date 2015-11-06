#ifndef OBJECT_GL_PROGRAM_INL
#define OBJECT_GL_PROGRAM_INL

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
	\file Program.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#include <string>

namespace ObjectGL{

	// Program

	Program::Program(Context& aContext):
		Object(aContext)
	{}

	Program::~Program(){
		if (IsCreated()) Destroy();

		// Remove all references to this program from the mContext
		bool erased = false;
		while ((!mContext.mProgramStack.empty()) && mContext.mProgramStack.back() == this){
			erased = true;
			mContext.mProgramStack.pop_back();
		}

		if(erased) glUseProgram(mContext.mProgramStack.empty() ? 0 : mContext.mProgramStack.back()->mID);

		auto it = std::find(mContext.mProgramStack.begin(), mContext.mProgramStack.end(), this);
		while(it != mContext.mProgramStack.end()){
			mContext.mProgramStack.erase(it);
			it = std::find(mContext.mProgramStack.begin(), mContext.mProgramStack.end(), this);
			erased = true;
		}
	}

	void Program::Attach(Shader& aShader){
		if(IsCreated()) throw std::runtime_error("ObjectGL::Program : Cannot attach shader after linking");
		mShaders.push_back(&aShader);
	}

	void Program::Create(){
		if(IsCreated()) throw std::runtime_error("ObjectGL::Program : Program has already been linked");

		mID = glCreateProgram();
		if(mID == Object::INVALID_ID) throw std::runtime_error("ObjectGL::Program : glCreateProgram returned invalid ID");
		
		for(const Shader* const shader : mShaders){
			glAttachShader(mID, static_cast<GLuint>(shader->GetID()));
		}

		glLinkProgram(mID);

		GLint status = 0;
		glGetProgramiv(mID, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			GLint logLength = 0;
			glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &logLength);

			std::string log(logLength, '\0');
			glGetProgramInfoLog(mID, logLength, &logLength, &log[0]);

			glDeleteProgram(mID);
			mID = 0;

			throw std::runtime_error(std::string("ObjectGL::Program : Failed to link program : ") + log.c_str());
		}

		for(const Shader* const shader : mShaders){
			glDetachShader(mID, static_cast<GLuint>(shader->GetID()));
		}
	}

	void Program::Destroy(){
		if(! IsCreated()) throw std::runtime_error("ObjectGL::Program : Program has not been linked");

		glDeleteProgram(mID);
		mID = 0;
	}

	void Program::OnContextCreated(){
		if(mContext.mProgramStack.empty() || mContext.mProgramStack.back() != this) glUseProgram(mID);
	}

	void Program::Bind(){
		mContext.mProgramStack.push_back(this);
		glUseProgram(mID);
	}

	void Program::Unbind(){
		if(mContext.mProgramStack.empty() || mContext.mProgramStack.back() != this) throw std::runtime_error("ObjectGL::Program : Program is not currently bound to Context");
		mContext.mProgramStack.pop_back();
		glUseProgram(mContext.mProgramStack.empty() ? 0 : mContext.mProgramStack.back()->mID);
	}

	bool Program::IsBound() const{
		return mContext.mProgramStack.empty() ? false : mContext.mProgramStack.back() == this;
	}

}

#endif
