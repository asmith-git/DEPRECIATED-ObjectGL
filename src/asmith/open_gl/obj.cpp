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

	static void obj_end_line(std::istream& aStream) throw() {
		if(aStream.eof()) return;
		char buf = aStream.peek();
		while(buf != '\n') {
			aStream.read(&buf, 1);
			if(aStream.eof()) return;
			buf = aStream.peek();
		}
	}

	static void obj_skip_whitespace(std::istream& aStream) throw() {
		//if(aStream.eof()) return;
		//char buf = aStream.peek();
		//while(std::isspace(buf)) {
		//	aStream.read(&buf, 1);
		//	if(aStream.eof()) return;
		//	buf = aStream.peek();
		//}
	}

	static void obj_read_v2(std::istream& aStream, vec2f& aValue) {
		aStream >> aValue[0];
		aStream >> aValue[1];
	}

	static void obj_read_v3(std::istream& aStream, vec3f& aValue) {
		aStream >> aValue[0];
		aStream >> aValue[1];
		aStream >> aValue[2];
	}

	static obj::face obj_read_face(std::istream& aStream) {
		char c;
		obj::face f;
		
		aStream >> f.vertex;
		obj_skip_whitespace(aStream);
		if(aStream.peek() != '/') {
			f.texture_coordinate = 1;
			f.normal = 1;
			return f;
		}
		aStream.read(&c, 1);
		obj_skip_whitespace(aStream);

		if(aStream.peek() == '/') {
			aStream.read(&c, 1);
			obj_skip_whitespace(aStream);
			aStream >> f.normal;
			obj_skip_whitespace(aStream);
			f.texture_coordinate = 1;
			return f;
		}
			
		aStream >> f.texture_coordinate;
		obj_skip_whitespace(aStream);
		if(aStream.peek() != '/') {
			f.normal = 1;
			return f;
		}
		aStream.read(&c, 1);
		obj_skip_whitespace(aStream);

		aStream >> f.normal;

		return f;
	}

	static const obj::triangle obj_read_triangle(std::istream& aStream) {
		const auto pos = aStream.tellg();
		uint32_t count = 0;

		char c;
		//aStream.read(&c, 1);
		//while(aStream.peek() != '\n') {
		//	aStream.read(&c, 1);
		//	if(c == '/') ++count;
		//}

		aStream.seekg(pos);

		obj::triangle v;

		//! \todo Break larger faces into triangles
		v.points[0]  = obj_read_face(aStream);
		v.points[1] = obj_read_face(aStream);
		v.points[2] = obj_read_face(aStream);


		return v;
	};
	
	// obj

	void obj::load(std::istream& aStream) {
		vertices.clear();
		texture_coordinates.clear();
		normals.clear();
		faces.clear();

		vec2f buf2;
		vec3f buf3;

		char c;
		while(! aStream.eof()) {
			aStream >> c;
			switch (c) {
			case '#':
				break;
			case 's':
				break;
			case 'f':
				faces.push_back(obj_read_triangle(aStream));
				break;
			case 'v':
				switch(aStream.peek()) {
				case 't':
					aStream.read(&c, 1);
					obj_read_v2(aStream, buf2);
					texture_coordinates.push_back(buf2);
					break;
				case 'n':
					aStream.read(&c, 1);
					obj_read_v3(aStream, buf3);
					normals.push_back(buf3);
					break;
				default:
					obj_read_v3(aStream, buf3);
					vertices.push_back(buf3);
					break;
				}
				break;
			default:
				throw std::runtime_error("asmith::gl::read_obj : Unexpected character found");
			}
			obj_end_line(aStream);
		}

		if(vertices.empty()) vertices.push_back({0.f, 0.f, 0.f});
		if(texture_coordinates.empty()) texture_coordinates.push_back({0.f, 0.f});
		if(normals.empty()) normals.push_back({0.f, 0.f, 1.f});
	}

	std::shared_ptr<vertex_array> obj::create_vao() const {
		struct vertex {
			vec3f v;
			vec2f t;
			vec3f n;
		};

		const size_t f = faces.size();
		std::vector<vertex> model(f * 3);
		for(size_t i = 0; i < f; ++i) {
			for(size_t j = 0; j < 3; ++j) {
				vertex& v = model[i*3 + j];
				v.v = vertices[faces[i].points[j].vertex - 1];
				v.t = texture_coordinates[faces[i].points[j].texture_coordinate - 1];
				v.n = normals[faces[i].points[j].normal - 1];
			}
		}

		std::shared_ptr<gl::vertex_buffer> vbo(new gl::vertex_buffer());
		std::shared_ptr<gl::vertex_array> vao(new gl::vertex_array());

		vbo->set_usage(GL_STATIC_DRAW);
		vbo->create();
		vbo->buffer(&model[0], model.size() * sizeof(vertex));

		vao->add_attribute(vbo, { 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(0) });
		vao->add_attribute(vbo, { 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(GLfloat) * 3) });
		vao->add_attribute(vbo, { 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(GLfloat) * 5) });
		vao->create();

		return vao;
	}
}}