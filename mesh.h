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
	hlm::mat4 transform;
	unsigned material;
	unsigned vbo, vao, num_vertices;
public:
	Mesh(const std::string& filename, unsigned mat);
	~Mesh();
	inline hlm::mat4& getTransform(){return transform;}
	inline unsigned getMaterial(){return material;}
	inline void setTransform(const hlm::mat4& xform){transform = xform;}
	inline void setMaterial(const unsigned mat){material = mat;}
	void draw();
};

#endif