#ifndef ENTITY_GRAPH_H
#define ENTITY_GRAPH_H

#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include <set>
#include <unordered_map>
#include <vector>

enum TRANFORM_TYPE{
	T,
	R,
	S
};

struct TransOp{
	hlm::vec4 data;
	TRANFORM_TYPE type;
	TransOp(const TRANFORM_TYPE _type, const hlm::vec4& _data) 
		: type(_type), data(_data){};
};

struct Transform{
	std::vector<TransOp> data;
	inline void add(const TransOp& t){
		data.push_back(t);
	}
	inline void add(const TRANFORM_TYPE type, const hlm::vec4& in){
		data.push_back(TransOp(type, in));
	}
	inline void add(const TRANFORM_TYPE type, const float x, const float y, const float z, const float w){
		data.push_back(TransOp(type, hlm::vec4(x, y, z, w)));
	}
	inline void add(const TRANFORM_TYPE type, const float x, const float y, const float z){
		data.push_back(TransOp(type, hlm::vec4(x, y, z, 0.0f)));
	}
	inline void add(const TRANFORM_TYPE type, const float s){
		data.push_back(TransOp(type, hlm::vec4(s)));
	}
	inline void clear(){
		data.clear();
	}
};

struct MeshTransform{
	hlm::mat4 mat;
	int mesh_id;
	MeshTransform(const int id, const hlm::mat4& inmat) : mesh_id(id), mat(inmat){};
};

struct Entity{
	hlm::mat4 transform;
	std::set<int> children, parents;
	int id, mesh_id;
	Entity(const int _id, const int _parent_id, const int _mesh_id, const Transform& trans);
};

class EntityGraph{
private:
	//would use map here for better memory, but gcc 4.9.2 is bugged
	std::unordered_map<int, Entity> entities;
	std::vector<MeshTransform> mesh_transforms;
	std::set<int> root_children;
	void update(const Entity& ent, const hlm::mat4& inmat);
public:
	inline void init(const int size){
		entities.reserve(size);
	};
	inline void destroy(){
		entities.clear();
		mesh_transforms.clear();
		root_children.clear();
	};
	int insert(const int id, const int parent_id, const int mesh_id, const Transform& trans);
	void remove(const int _id);
	int addParent(const int _id, const int _parent_id);
	void update();
	inline void getTransforms(std::vector<MeshTransform>** out_vec){ *out_vec = &mesh_transforms; };
};

#endif