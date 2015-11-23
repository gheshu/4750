#include "entitygraph.h"
#include <algorithm>
#include "util.h"
#include <iostream>

Entity::Entity(unsigned _id, Entity* parent_ptr, int _mesh_id, const Transform& trans) : id(_id), mesh_id(_mesh_id) {
	if(parent_ptr)
		parents.insert(parent_ptr);
	for(TransOp i : trans.data){
		switch(i.type){
			case T:
				transform = transform * hlm::translate(i.data);
				break;
			case R:
				transform = transform * hlm::rotateEuler(i.data);
				break;
			case S:
				transform = transform * hlm::scale(i.data);
				break;
		}
	}
}

void Entity::addChild(Entity* ent){
	if(parents.find(ent) != parents.end()){	// check to ensure ent isn't a parent of this node
		std::cerr << "Adding child " << ent->id << " would cause a cycle with " << id << std::endl;
		return;
	}
	if(ent->children.find(this) != ent->children.end()){ // check to ensure this isn't a child of ent
		std::cerr << "Adding child " << ent->id << " would cause a cycle with " << id << std::endl;
		return;
	}
	children.insert(ent);	// bidirectional link
	ent->parents.insert(this);
}

void Entity::removeChild(Entity* ent){
	children.insert(ent->children.begin(), ent->children.end());
	// need to remove ent from its children's parent set.
	for(auto i : ent->children){
		i->parents.erase(ent);
		i->parents.insert(this);
	}
	children.erase(ent);
}
void Entity::rotate(const hlm::vec4& v){
	transform = transform * hlm::rotate(v);
}
void Entity::scale(const hlm::vec3& v){
	transform = transform * hlm::scale(v);
}
void Entity::translate(const hlm::vec3& v){
	transform = transform * hlm::translate(v);
}
void Entity::setTransform(const Transform& trans){
	transform = hlm::mat4();
	for(TransOp i : trans.data){
		switch(i.type){
			case T:
				transform = transform * hlm::translate(i.data);
				break;
			case R:
				transform = transform * hlm::rotate(i.data);
				break;
			case S:
				transform = transform * hlm::scale(i.data);
				break;
		}
	}
}

void EntityGraph::init(const int size){
	entities.clear();
	entities.reserve(size);
	entities.add(0, Entity());
}

void EntityGraph::destroy(){
	entities.clear();
	mesh_transforms.clear();
}

void EntityGraph::insert(unsigned id, unsigned parent_id, int mesh_id, const Transform& trans){
	if(entities.get(id)){
		std::cerr << "Entity " << id << " already exists\n";
		return;
	}
	Entity* parent = entities.get(parent_id);
	if(nullptr == parent){
		std::cerr << "Parent Entity " << parent_id << " doesn't exist\n";
		return;
	}
	entities.add(id, Entity(id, parent, mesh_id, trans));
	Entity* ent = entities.get(id);
	parent->addChild(ent);
}
void EntityGraph::remove(unsigned id){
	Entity* item = entities.get(id);
	if(item == nullptr){
		std::cerr << "Entity " << id << " doesn't exist\n";
		return;
	}
	for(Entity* i : item->parents){
		i->removeChild(item);
	}
	entities.remove(id);
}
void EntityGraph::addParent(unsigned _id, unsigned _parent_id){
	if(_id == 0){
		std::cerr << "Cannot make anything the parent of root\n";
		return;
	}
	Entity* i = entities.get(_id);
	if(i == nullptr){
		std::cerr << "Entity " << _id << " doesn't exist\n";
		return;
	}
	Entity* p = entities.get(_parent_id);
	if(p == nullptr){
		std::cerr << "Parent " << _parent_id << " doesn't exist\n";
		return;
	}
	p->addChild(i);
}

void EntityGraph::update(){
	{
		mesh_transforms.clear();
		const int reserve_size = hlm::clamp(8, 1024, (int)entities.size() / 4);
		mesh_transforms.reserve(reserve_size);
	}
	Entity* root = entities.get(0);
	for(auto i : root->children){
		update(i, hlm::mat4());
	}
}
void EntityGraph::update(Entity* ent, const hlm::mat4& inmat){
	hlm::mat4 outmat = inmat * ent->transform;
	if(ent->mesh_id >= 0){
		mesh_transforms.add((unsigned)ent->mesh_id, outmat);
	}
	for(auto a : ent->children){
		update(a, outmat);
	}
}

void EntityGraph::translate(unsigned id, const hlm::vec3& v){
	Entity* i = entities.get(id);
	if(i) i->translate(v);
}
void EntityGraph::rotate(unsigned id, const hlm::vec4& v){
	Entity* i = entities.get(id);
	if(i) i->rotate(v);
}
void EntityGraph::scale(unsigned id, const hlm::vec3& v){
	Entity* i = entities.get(id);
	if(i) i->scale(v);
}
void EntityGraph::setTransform(unsigned id, const Transform& trans){
	Entity* i = entities.get(id);
	if(i) i->setTransform(trans);
}