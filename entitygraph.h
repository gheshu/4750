#ifndef ENTITY_GRAPH_H
#define ENTITY_GRAPH_H

#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include <set>
#include <unordered_map>
#include <vector>
#include <string>
#include "instancetransform.h"

enum TRANSFORM_TYPE { T,R,S };

struct TransOp{
	hlm::vec4 data;
	TRANSFORM_TYPE type;
	TransOp(const TRANSFORM_TYPE _type, const hlm::vec4& _data) 
		: data(_data), type(_type) {};
};

struct Transform{
	std::vector<TransOp> data;
	inline void add(const TRANSFORM_TYPE type, const hlm::vec4& in){data.push_back(TransOp(type, in));}
	inline void clear(){data.clear();}
};

struct Entity{
	hlm::mat4 transform;
	std::set<Entity*> children, parents;
	std::string id;
	bool hasMesh;
	Entity(const std::string& _id, Entity* parent_ptr, bool _hasMesh, const Transform& trans);
	void addChild(Entity* ent);
	void removeChild(Entity* ent);
	void rotate(const hlm::vec4& v);
	void scale(const hlm::vec3& v);
	void translate(const hlm::vec3& v);
	void setTransform(const Transform& trans);
};

class EntityGraph{
private:
	std::unordered_map<std::string, Entity*> entities;
	TransformList mesh_transforms;
	Entity* root = nullptr;
	void update(Entity* ent, const hlm::mat4& inmat);
public:
	void init(const int size);
	void destroy();
	void insert(const std::string& id, const std::string& parent_id, bool hasMesh, const Transform& trans);
	void remove(const std::string& _id);
	void addParent(const std::string& _id, const std::string& _parent_id);
	void update();
	inline TransformList* getTransforms(){ return &mesh_transforms; };
	void translate(const std::string& id, const hlm::vec3& v);
	void rotate(const std::string& id, const hlm::vec4& v);
	void scale(const std::string& id, const hlm::vec3& v);
	void setTransform(const std::string& id, const Transform& trans);
};

#endif