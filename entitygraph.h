#ifndef ENTITY_GRAPH_H
#define ENTITY_GRAPH_H

#include "hlm.h"
#include <set>
#include <unordered_map>

struct Transform{
	hlm::vec3 translation, rotation, scale;
	float angle = 0.0f;
	Transform(hlm::vec3& trans, float _angle, hlm::vec3& rot, hlm::vec3& _scale) : 
		translation(trans), angle(_angle), rotation(rot), scale(_scale){};
	Transform(){};
};

struct Entity{
	hlm::mat4 transform;
	std::set<int> children;
	int id, mesh_id, parent_id;
	Entity(int _id, int _mesh_id, int _parent_id, const Transform& trans);
	Entity(int _id) : id(_id){};
};

class EntityGraph{
private:
	std::unordered_map<int, Entity> entities;
	std::set<int> root_children;
public:
	void init(int size);
	void destroy();
	int insert(const Entity& ent);
	void remove(int _id);
	void getWorldTransform(int _id, hlm::mat4& out_mat);
};

#endif