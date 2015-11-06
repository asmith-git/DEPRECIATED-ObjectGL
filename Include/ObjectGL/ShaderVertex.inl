#ifndef OBJECT_GL_VERTEX_SHADER_INL
#define OBJECT_GL_VERTEX_SHADER_INL

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
	\file ShaderVertex.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL{

	// VertexShader

	VertexShader::VertexShader(Context& aContext, SourceFactory& aSource) :
		Shader(aContext, aSource)
	{}

	VertexShader::~VertexShader(){

	}

	Shader::Type VertexShader::GetType() const{
		return Shader::Type::VERTEX;
	}

	GLuint VertexShader::GetMaxUniformComponents() const{
		return GL_MAX_VERTEX_UNIFORM_COMPONENTS;
	}

	GLuint VertexShader::GetMaxUniformBlocks() const{
		return GL_MAX_VERTEX_UNIFORM_BLOCKS;
	}

	GLuint VertexShader::GetMaxInputComponents() const{
		return 0;
	}

	GLuint VertexShader::GetMaxOutputComponents() const{
		return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
	}

	GLuint VertexShader::GetMaxTextureImageUnits() const{
		return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
	}


}

#endif
