#ifndef OBJECT_GL_COMPUTE_SHADER_INL
#define OBJECT_GL_COMPUTE_SHADER_INL

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
	\file ShaderCompute.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#if (OBJECT_GL_MAX_VERISON_MAJOR < 4) || (OBJECT_GL_MAX_VERISON_MAJOR == 4 && OBJECT_GL_MAX_VERISON_MINOR < 3)
	#error ObjectGL : ComputeShader is only avalible in OpenGL 4.3 or greater
#endif

namespace ObjectGL{

	// ShaderCompute

	ComputeShader::ComputeShader(Context& aContext, SourceFactory& aSource) :
		Shader(aContext, aSource)
	{}

	ComputeShader::~ComputeShader(){

	}

	Shader::Type ComputeShader::GetType() const{
		return Shader::Type::COMPUTE;
	}

	GLuint ComputeShader::GetMaxUniformComponents() const{
		return GL_MAX_COMPUTE_UNIFORM_COMPONENTS;
	}

	GLuint ComputeShader::GetMaxUniformBlocks() const{
		return GL_MAX_COMPUTE_UNIFORM_BLOCKS;
	}

	GLuint ComputeShader::GetMaxInputComponents() const{
		return GL_MAX_COMPUTE_INPUT_COMPONENTS;
	}

	GLuint ComputeShader::GetMaxOutputComponents() const{
		return GL_MAX_COMPUTE_OUTPUT_COMPONENTS;
	}

	GLuint ComputeShader::GetMaxTextureImageUnits() const{
		return GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS;
	}


}

#endif
