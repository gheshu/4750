#ifndef MESH_H
#define MESH_H

#include "hlm.h"
#include <vector>
#include <string>
#include <tuple>

struct MeshVertex{
	hlm::vec3 position;
	hlm::vec3 normal;
	hlm::vec2 uv;
};

typedef std::vector<MeshVertex> VertexBuffer;
typedef std::vector<unsigned> IndexBuffer;
struct MeshData{
	VertexBuffer vertices;
	IndexBuffer indices;
	inline MeshVertex& at(const int i){return vertices[i];}
	inline MeshVertex& atIndex(const int i){return vertices[indices[i]];}
};

class Mesh{
	unsigned vbo, vao, ibuf, num_indices;
public:
	Mesh(const std::string& filename);
	~Mesh();
	void draw();
};

typedef std::vector<Mesh> MeshList;

#endif
