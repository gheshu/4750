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
typedef std::vector<int> IndexBuffer;
typedef std::pair<VertexBuffer, IndexBuffer> MeshData;

class Mesh{
	hlm::mat4 transform;
	std::string material;
	unsigned vbo, vao, num_vertices;
public:
	Mesh(const std::string& filename, const std::string& mat) : material(mat);
	inline hlm::mat4& getTransform(){return transform;}
	inline std::string& getMaterial(){return material;}
	inline void setTransform(const hlm::mat4& xform){transform = xform;}
	inline void setMaterial(const unsigned material){mat_id = material;}
	void draw();
	inline bool operator < (const Mesh& other){ return material < other.material 
		|| (material == other.material && vao < other.vao); }
};

#endif