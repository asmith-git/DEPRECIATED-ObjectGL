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
#include "asmith/utilities/strings.hpp"
#include <cctype>

namespace asmith { namespace gl {

	static inline const char* obj_skip_whitespace(const char* aPos) throw() {
		while(std::isspace(*aPos))++aPos;
		return aPos;
	}

	static inline const char* obj_read_f(const char* aPos, GLfloat& aValue) {
		aPos = obj_skip_whitespace(aPos);
		const char* p = strings::read_f(aPos, aValue);
		if(p == aPos) throw std::runtime_error("asmith::gl::obj::read_obj : expected float");
		return p;
	}

	static inline const char* obj_read_u(const char* aPos, GLuint& aValue) {
		aPos = obj_skip_whitespace(aPos);
		const char* p = strings::read_32u(aPos, aValue);
		if(p == aPos) throw std::runtime_error("asmith::gl::obj::read_obj : expected unsigned integer");
		return p;
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
			if(aValue.count >= obj::MAX_FACE_POINTS) throw std::runtime_error("asmith::gl::obj::read_obj : MAX_FACE_POINTS exceeded");
			aPos = obj_read_face(aPos, aValue.faces[aValue.count++]);
		}
		return aPos;
	};
	
	// obj

	void obj::load(std::istream& aStream) {
		vertices.clear();
		texture_coordinates.clear();
		normals.clear();
		objects.clear();

		object* currentObject = nullptr;
		group* currentGroup = nullptr;

		vec2f buf2;
		vec3f buf3;
		primative buffp;

		char c;
		char line[256];
		uint8_t length = 0;
		bool smooth = false;

		bool materialError = true;

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
				pos = obj_skip_whitespace(pos + 1);
				if(*pos == '1') {
					smooth = true;
				}else if(*pos == '0') {
					smooth = false;
				}else if(*pos == 'o') {
					++pos;
					if(*pos == 'n') {
						smooth = true;
					}else if(*pos == 'f') {
						smooth = false;
					}else {
						throw std::runtime_error("asmith::gl::obj::read_obj : Unexpected character found");
					}
				}else {
					throw std::runtime_error("asmith::gl::obj::read_obj : Unexpected character found");
				}
				break;
			case 'm':
			case 'u':
				if(materialError) {
					materialError = false;
					std::cerr << "asmith::gl::obj::read_obj : Materials not implemented" << std::endl;
				}
				break;
			case 'o':
				pos = obj_skip_whitespace(pos + 1);
				objects.push_back(object());
				currentObject = &objects.back();
				currentObject = nullptr;

				while(*pos != '\0') {
					currentObject->name += *pos;
					++pos;
				}
				break;
			case 'g':
				if(currentObject == nullptr) {
					objects.push_back(object());
					currentObject = &objects.back();
				}

				pos = obj_skip_whitespace(pos + 1);
				currentObject->groups.push_back(group());
				currentGroup = &currentObject->groups.back();

				while(*pos != '\0') {
					currentGroup->name += *pos;
					++pos;
				}
				break;
			case 'f':
				if(currentObject == nullptr) {
					objects.push_back(object());
					currentObject = &objects.back();
				}
				if(currentGroup == nullptr) {
					currentObject->groups.push_back(group());
					currentGroup = &currentObject->groups.back();
				}
				pos = obj_read_primative(pos + 1, buffp);
				buffp.smooth_shading = smooth ? 1 : 0;
				currentGroup->faces.push_back(buffp);
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

	std::shared_ptr<vertex_array> obj::create_vao(context& aContext, GLsizei & aVerts) const {
		struct vertex {
			vec3f v;
			vec2f t;
			vec3f n;
		};

		aVerts = 0;
		for(const object& o : objects) for(const group& g : o.groups) aVerts += g.faces.size();

		std::vector<vertex> model(aVerts * 3);
		size_t index = 0;
		for(const object& obj : objects) {
			for(const group& grp : obj.groups) {
				const size_t f2 = grp.faces.size();
				for(size_t i = 0; i < f2; ++i) {
					const primative& p = grp.faces[i];
					if(p.count == 3) {
						// Triangular faces
						for(size_t j = 0; j < 3; ++j) {
							vertex& v = model[index++];
							v.v = vertices[p.faces[j].vertex - 1];
							v.t = texture_coordinates[p.faces[j].texture_coordinate - 1];
							v.n = normals[p.faces[j].normal - 1];
						}
					}else {
						// Non-triangular faces
						const size_t newVerts = (p.count - 3) * 3;
						aVerts += newVerts;
						for(size_t j = 0; j < newVerts; ++j) model.push_back(vertex());
						for(size_t j = 1; j < p.count - 1; ++j) {
							vertex& v1 = model[index++];
							vertex& v2 = model[index++];
							vertex& v3 = model[index++];

							v1.v = vertices[p.faces[0].vertex - 1];
							v1.t = texture_coordinates[p.faces[0].texture_coordinate - 1];
							v1.n = normals[p.faces[0].normal - 1];

							v2.v = vertices[p.faces[j].vertex - 1];
							v2.t = texture_coordinates[p.faces[j].texture_coordinate - 1];
							v2.n = normals[p.faces[j].normal - 1];

							v3.v = vertices[p.faces[j + 1].vertex - 1];
							v3.t = texture_coordinates[p.faces[j + 1].texture_coordinate - 1];
							v3.n = normals[p.faces[j + 1].normal - 1];
						}
					}
				}
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