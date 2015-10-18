#ifndef MESH_H
#define MESH_H

#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include <vector>
#include <string>

struct MeshVertex{
	hlm::vec4 position;
	hlm::vec3 normal, color;
	hlm::vec2 uv;
};

struct Mesh{
	std::vector<MeshVertex> vertices;
	std::vector<unsigned> indices;
	
	inline MeshVertex& atIndex(const unsigned i){
		return vertices[indices[i]];
	}
	inline MeshVertex& at(const unsigned i){
		return vertices[i];
	}
	inline unsigned num_indices(){ return indices.size(); }
	inline unsigned num_verts() {return vertices.size(); }
};

#endif