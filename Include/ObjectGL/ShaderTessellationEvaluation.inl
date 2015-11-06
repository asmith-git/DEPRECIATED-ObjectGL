#ifndef OBJECT_GL_TESS_EVALUATION_SHADER_INL
#define OBJECT_GL_TESS_EVALUATION_SHADER_INL

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
	\file ShaderTessellationEvaluation.inl
	\brief
	\author Adam Smith
	\date 6th November 2015
*/

#if OBJECT_GL_MAX_VERISON_MAJOR < 4
	#error ObjectGL : TessellationEvaluationShader is only avalible in OpenGL 4.0 or greater
#endif

namespace ObjectGL{

	// ShaderTessellationEvaluation

	TessellationEvaluationShader::TessellationEvaluationShader(Context& aContext, SourceFactory& aSource) :
		Shader(aContext, aSource)
	{}

	TessellationEvaluationShader::~TessellationEvaluationShader(){

	}

	Shader::Type TessellationEvaluationShader::GetType() const{
		return Shader::Type::TESSELLATION_EVALUATION;
	}

	GLuint TessellationEvaluationShader::GetMaxUniformComponents() const{
		return GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS;
	}

	GLuint TessellationEvaluationShader::GetMaxUniformBlocks() const{
		return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
	}

	GLuint TessellationEvaluationShader::GetMaxInputComponents() const{
		return GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS;
	}

	GLuint TessellationEvaluationShader::GetMaxOutputComponents() const{
		return GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS;
	}

	GLuint TessellationEvaluationShader::GetMaxTextureImageUnits() const{
		return GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS;
	}


}

#endif
