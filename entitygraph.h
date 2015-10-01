#ifndef ENTITY_GRAPH_H
#define ENTITY_GRAPH_H

#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include <set>
#include <unordered_map>
#include <vector>
#include <string>

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
	std::string mesh_id;
	MeshTransform(const std::string& id, const hlm::mat4& inmat) : mesh_id(id), mat(inmat){};
};

struct Entity{
	hlm::mat4 transform;
	std::set<Entity*> children, parents;
	std::string id, mesh_id;
	Entity(const std::string& _id, Entity* parent_ptr, const std::string& _mesh_id, const Transform& trans);
	void addChild(Entity* ent);
	void removeChild(Entity* ent);
	void rotate(const hlm::vec4& v);
	void scale(const hlm::vec3& v);
	void translate(const hlm::vec3& v);
	void setTransform(const Transform& trans);
};

class EntityGraph{
private:
	//would use map here for better memory, but gcc 4.9.2 is bugged
	std::unordered_map<std::string, Entity*> entities;
	std::vector<MeshTransform> mesh_transforms;
	Entity* root = nullptr;
	void update(Entity* ent, const hlm::mat4& inmat);
public:
	void init(const int size);
	void destroy();
	void insert(const std::string& id, const std::string& parent_id, const std::string& mesh_id, const Transform& trans);
	void remove(const std::string& _id);
	void addParent(const std::string& _id, const std::string& _parent_id);
	void update();
	inline std::vector<MeshTransform>* getTransforms(){ return &mesh_transforms; };
	void translate(const std::string& id, const hlm::vec3& v);
	void rotate(const std::string& id, const hlm::vec4& v);
	void scale(const std::string& id, const hlm::vec3& v);
	void setTransform(const std::string& id, const Transform& trans);
};

#endif