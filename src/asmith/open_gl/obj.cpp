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

namespace asmith { namespace gl {
	
	// obj

	void obj::load(std::istream& aStream) {

		const auto end_line = [&]()->void {
			char buf;
			if(aStream.eof()) return;
			aStream.read(&buf, 1);
			while(aStream.eof() || buf != '\n') aStream.read(&buf, 1);
		};

		const auto read_v2 = [&]()->vec2f {
			vec2f v;
			aStream >> v[0];
			aStream >> v[1];
			return v;
		};

		const auto read_v3 = [&]()->vec3f {
			vec3f v;
			aStream >> v[0];
			aStream >> v[1];
			aStream >> v[2]; 
			return v;
		};

		const auto read_read_triangle = [&]()->triangle {
			const auto pos = aStream.tellg();
			uint32_t count = 0;

			char c;
			//aStream.read(&c, 1);
			//while(aStream.peek() != '\n') {
			//	aStream.read(&c, 1);
			//	if(c == '/') ++count;
			//}

			aStream.seekg(pos);

			triangle v;

			//! \todo Handle different face formats
			//! \todo Break larger faces into triangles
			//! \todo Handle materials
			//! \todo Handle smooth shading (s 1) 

			//switch(count) {
			//case 0:	// v v v
			//	aStream >> v[0][0];
			//	v[0][1] = 0;
			//	v[0][2] = 0;

			//	aStream >> v[1][0];
			//	v[1][1] = 0;
			//	v[1][2] = 0;

			//	aStream >> v[2][0];
			//	v[2][1] = 0;
			//	v[2][2] = 0;
			//	break;
			//case 3:	// v/n v/n v/n
			//	aStream >> v[0][0];
			//	aStream >> c;
			//	aStream >> v[0][1];
			//	v[0][2] = 0;

			//	aStream >> v[1][0];
			//	aStream >> c;
			//	aStream >> v[1][1];
			//	v[1][2] = 0;

			//	aStream >> v[2][0];
			//	aStream >> c;
			//	aStream >> v[2][1];
			//	v[2][2] = 0;
			//	break;
			//case 9:	// v/n/t v/n/t v/n/t
				aStream >> v.points[0].vertex;
				aStream >> c;
				if(aStream.peek() == '/') {
					v.points[0].texture_coordinate = 1;
				}else {
					aStream >> v.points[0].texture_coordinate;
				}
				aStream >> c;
				aStream >> v.points[0].normal;

				aStream >> v.points[1].vertex;
				aStream >> c;
				if (aStream.peek() == '/') {
					v.points[1].texture_coordinate = 1;
				}else {
					aStream >> v.points[1].texture_coordinate;
				}
				aStream >> c;
				aStream >> v.points[1].normal;

				aStream >> v.points[2].vertex;
				aStream >> c;
				if (aStream.peek() == '/') {
					v.points[2].texture_coordinate = 1;
				}else {
					aStream >> v.points[2].texture_coordinate;
				}
				aStream >> c;
				aStream >> v.points[2].normal;
			//	break;
			//default:
			//	throw std::runtime_error("asmith::gl::read_obj : Unexpected face format detected");
			//}


			//! \todo Implement
			return v;
		};

		vertices.clear();
		texture_coordinates.clear();
		normals.clear();
		faces.clear();

		char c;
		while(! aStream.eof()) {
			aStream >> c;
			switch (c) {
			case 'f':
				faces.push_back(read_read_triangle());
				break;
			case 'v':
				switch(aStream.peek()) {
				case 't':
					aStream.read(&c, 1);
					texture_coordinates.push_back(read_v2());
					break;
				case 'n':
					aStream.read(&c, 1);
					normals.push_back(read_v3());
					break;
				default:
					vertices.push_back(read_v3());
					break;
				}
				break;
			default:
				throw std::runtime_error("asmith::gl::read_obj : Unexpected character found");
			}
			end_line();
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