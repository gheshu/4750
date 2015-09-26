#ifndef ENTITY_GRAPH_H
#define ENTITY_GRAPH_H

#include "hlm.h"
#include <set>
#include <unordered_map>
#include <vector>

struct Transform{
	hlm::vec3 translation, rotation, scale;
	float angle = 0.0f;
	Transform(const hlm::vec3& trans, const float _angle, const hlm::vec3& rot, const hlm::vec3& _scale) : 
		translation(trans), angle(_angle), rotation(rot), scale(_scale){};
	Transform(){};
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
	std::unordered_map<int, Entity> entities;
	std::vector<MeshTransform> mesh_transforms;
	std::set<int> root_children;
	void update(const Entity& ent, const hlm::mat4& inmat);
public:
	void init(const int size);
	void destroy();
	int insert(const Entity& ent);
	void remove(const int _id);
	void addParent(const int _id, const int _parent_id);
	void update();
	inline void getTransforms(std::vector<MeshTransform>& out_vec){out_vec = mesh_transforms;};
};

#endif