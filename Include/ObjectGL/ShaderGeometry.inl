#ifndef OBJECT_GL_GEOMETRY_SHADER_INL
#define OBJECT_GL_GEOMETRY_SHADER_INL

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
	\file ShaderGeometry.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

namespace ObjectGL{

	// ShaderGeometry

	GeometryShader::GeometryShader(Context& aContext, SourceFactory& aSource) :
		Shader(aContext, aSource)
	{}

	GeometryShader::~GeometryShader(){

	}

	Shader::Type GeometryShader::GetType() const{
		return Shader::Type::GEOMETRY;
	}

	GLuint GeometryShader::GetMaxUniformComponents() const{
		return GL_MAX_GEOMETRY_UNIFORM_COMPONENTS;
	}

	GLuint GeometryShader::GetMaxUniformBlocks() const{
		return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
	}

	GLuint GeometryShader::GetMaxInputComponents() const{
		return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
	}

	GLuint GeometryShader::GetMaxOutputComponents() const{
		return GL_MAX_GEOMETRY_OUTPUT_COMPONENTS;
	}

	GLuint GeometryShader::GetMaxTextureImageUnits() const{
		return GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS;
	}


}

#endif
