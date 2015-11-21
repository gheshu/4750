#ifndef MESH_H
#define MESH_H

#include "hlm.h"
#include <vector>

struct MeshVertex{
	hlm::vec3 position;
	hlm::vec3 normal;
	hlm::vec2 uv;
};

typedef std::vector<MeshVertex> VertexBuffer;
typedef std::vector<int> IndexBuffer;

struct Mesh{
	hlm::mat4 transform;
	unsigned vbo, vao, ibuf, num_indices;
	Mesh();
	~Mesh();
	void uploadData(VertexBuffer& verts, IndexBuffer& indices);
	void draw();
};

#endif