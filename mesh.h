#ifndef MESH_H
#define MESH_H

#include "hlm.h"
#include <vector>
#include <string>

struct MeshVertex{
	hlm::vec3 position;
	hlm::vec3 normal;
	hlm::vec2 uv;
};

typedef std::vector<MeshVertex> VertexBuffer;
typedef std::vector<int> IndexBuffer;

struct MeshData{
	VertexBuffer vertices;
	IndexBuffer indices;
	unsigned vbo, vao, ibuf, num_indices;
	MeshData(const std::string& filename);
	~MeshData();
	void draw();
};

class Mesh{
	hlm::mat4 transform;
	std::string material;
	MeshData* data;
public:
	Mesh(const hlm::mat4& xform = hlm::mat4(), const std::string& mat, MeshData* d = nullptr) 
		: transform(xform), material(mat), data(d){};
	inline hlm::mat4& getTransform(){return transform;}
	inline std::string& getMaterial(){return material;}
	inline void setTransform(const hlm::mat4& xform){transform = xform;}
	inline void setMaterial(const unsigned material){mat_id = material;}
	inline void draw(){data->draw();}
	inline void setMeshData(MeshData& d){data = d;}
	inline bool operator < (const Mesh& other){ return material < other.material; }
};

#endif