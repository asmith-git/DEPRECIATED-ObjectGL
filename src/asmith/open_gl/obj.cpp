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

#include "asmith/open_gl/obj.hpp"
#include <cctype>

namespace asmith { namespace gl {

	static inline const char* obj_skip_whitespace(const char* aPos) throw() {
		while(std::isspace(*aPos))++aPos;
		return aPos;
	}

	static const char* obj_read_f(const char* aPos, GLfloat& aValue) {
		aPos = obj_skip_whitespace(aPos);
		aValue = std::atof(aPos);
		while((*aPos >= '0' && *aPos <= '9') || *aPos == '-' || *aPos == '.') ++aPos;
		return aPos;
	}

	static const char* obj_read_u(const char* aPos, GLuint& aValue) {
		aPos = obj_skip_whitespace(aPos);
		aValue = std::atoi(aPos);
		while (*aPos >= '0' && *aPos <= '9') ++aPos;
		return aPos;
	}

	static inline const char* obj_read_v2(const char* aPos, vec2f& aValue) {
		aPos = obj_read_f(aPos, aValue[0]);
		aPos = obj_read_f(aPos, aValue[1]);
		return aPos;
	}

	static inline const char* obj_read_v3(const char* aPos, vec3f& aValue) {
		aPos = obj_read_f(aPos, aValue[0]);
		aPos = obj_read_f(aPos, aValue[1]);
		aPos = obj_read_f(aPos, aValue[2]);
		return aPos;
	}

	static const char* obj_read_face(const char* aPos, obj::face& aValue) {
		aPos = obj_read_u(aPos, aValue.vertex);
		aPos = obj_skip_whitespace(aPos);
		if(*aPos != '/') {
			aValue.texture_coordinate = 1;
			aValue.normal = 1;
			return aPos;
		}
		aPos = obj_skip_whitespace(aPos + 1);

		if(*aPos == '/') {
			aPos = obj_skip_whitespace(aPos + 1);
			aPos = obj_read_u(aPos, aValue.normal);
			aValue.texture_coordinate = 1;
			return aPos;
		}

		aPos = obj_read_u(aPos, aValue.texture_coordinate);
		aPos = obj_skip_whitespace(aPos);
		if(*aPos != '/') {
			aValue.normal = 1;
			return aPos;
		}
		aPos = obj_skip_whitespace(aPos + 1);
		aPos = obj_read_u(aPos, aValue.normal);

		return aPos;
	}

	static const char* obj_read_primative(const char* aPos, obj::primative& aValue) {
		aValue.count = 0;
		while(*aPos != '\0') {
			aPos = obj_skip_whitespace(aPos);
			if(aValue.count >= 8) throw std::runtime_error("asmith::gl::obj::read_obj : Maximum number of face points exceeded");
			aPos = obj_read_face(aPos, aValue.faces[aValue.count++]);
		}
		return aPos;
	};
	
	// obj

	void obj::load(std::istream& aStream) {
		vertices.clear();
		texture_coordinates.clear();
		normals.clear();
		faces.clear();

		vec2f buf2;
		vec3f buf3;
		primative buffp;

		char c;
		char line[256];
		uint8_t length = 0;

		while(! aStream.eof()) {
			// Read line
			length = 0;
			aStream.read(&c, 1);
			while(c != '\n' && ! aStream.eof()) {
				if(length == UINT8_MAX) throw std::runtime_error("asmith::gl::obj::read_obj : Maximum line length exceeded");
				line[length++] = c;
				aStream.read(&c, 1);
			}
			if(length == 0) continue;
			line[length] = '\0';

			const char* pos = obj_skip_whitespace(line);

			// Process line
			switch(*pos) {
			case '#':
				break;
			case 's':
				break;
			case 'm':
				throw std::runtime_error("asmith::gl::obj::read_obj : Materials not implemented");
			case 'g':
				throw std::runtime_error("asmith::gl::obj::read_obj : Groups not implemented");
			case 'f':
				pos = obj_read_primative(pos + 1, buffp);
				faces.push_back(buffp);
				break;
			case 'v':
				switch(pos[1]) {
				case 't':
					pos = obj_read_v2(pos + 2, buf2);
					texture_coordinates.push_back(buf2);
					break;
				case 'n':
					pos = obj_read_v3(pos + 2, buf3);
					normals.push_back(buf3);
					break;
				default:
					pos = obj_read_v3(pos + 1, buf3);
					vertices.push_back(buf3);
					break;
				}
				break;
			default:
				throw std::runtime_error("asmith::gl::obj::read_obj : Unexpected character found");
			}
		}

		if(vertices.empty()) vertices.push_back({0.f, 0.f, 0.f});
		if(texture_coordinates.empty()) texture_coordinates.push_back({0.f, 0.f});
		if(normals.empty()) normals.push_back({0.f, 0.f, 1.f});
	}

	std::shared_ptr<vertex_array> obj::create_vao(context& aContext) const {
		struct vertex {
			vec3f v;
			vec2f t;
			vec3f n;
		};

		const size_t f = faces.size();
		std::vector<vertex> model(f * 3);
		for(size_t i = 0; i < f; ++i) {
			//! \todo Break larger faces into triangles
			if(faces[i].count != 3) throw std::runtime_error("asmith::gl::obj::create_vao : Non-triangular face detected");
			for(size_t j = 0; j < 3; ++j) {
				vertex& v = model[i*3 + j];
				v.v = vertices[faces[i].faces[j].vertex - 1];
				v.t = texture_coordinates[faces[i].faces[j].texture_coordinate - 1];
				v.n = normals[faces[i].faces[j].normal - 1];
			}
		}

		std::shared_ptr<gl::vertex_buffer> vbo(new gl::vertex_buffer(aContext));
		std::shared_ptr<gl::vertex_array> vao(new gl::vertex_array(aContext));

		vbo->set_usage(GL_STATIC_DRAW);
		vbo->buffer(&model[0], model.size() * sizeof(vertex));

		vao->add_attribute(vbo, { 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(0) });
		vao->add_attribute(vbo, { 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(GLfloat) * 3) });
		vao->add_attribute(vbo, { 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(GLfloat) * 5) });

		return vao;
	}
}}