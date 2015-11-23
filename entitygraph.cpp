#include "entitygraph.h"
#include <algorithm>
#include "util.h"
#include <iostream>

Entity::Entity(unsigned _id, Entity* parent_ptr, bool _hasMesh, const Transform& trans) 
	: id(_id), hasMesh(_hasMesh) {
	if(parent_ptr){
		parents.insert(parent_ptr);
	}
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
	if(root != nullptr){
		std::cerr << "Cannot initialize entitygraph, root already exists\n";
		return;
	}
	entities.reserve(size);
	root = new Entity(0, nullptr, false, Transform());
	entities.insert({0, root});
}

void EntityGraph::destroy(){
	for(auto i : entities){
		delete i.second;
	}
	root = nullptr;
	entities.clear();
	mesh_transforms.clear();
}

void EntityGraph::insert(unsigned id, unsigned parent_id, bool hasMesh, const Transform& trans){
	if(entities.find(id) != entities.end()){
		std::cerr << "Entity " << id << " already exists\n";
		return;
	}
	auto parent_iterator = entities.find(parent_id);
	if(parent_iterator == entities.end()){
		std::cerr << "Parent Entity " << parent_id << " doesn't exist\n";
		return;
	}
	Entity* ent = new Entity(id, parent_iterator->second, hasMesh, trans);
	parent_iterator->second->addChild(ent);	// bi directional method, makes a double-link
	entities.insert({id, ent});
}
void EntityGraph::remove(unsigned id){
	auto iterator = entities.find(id);
	if(iterator == entities.end()){
		std::cerr << "Entity " << id << " doesn't exist\n";
		return;
	}
	Entity* ent = iterator->second;
	for(Entity* i : ent->parents){
		i->removeChild(ent);
	}
	delete ent;
	entities.erase(iterator);
}
void EntityGraph::addParent(unsigned _id, unsigned _parent_id){
	if(_id == 0){
		std::cerr << "Cannot make anything the parent of root\n";
		return;
	}
	auto i = entities.find(_id);
	if(i == entities.end()){
		std::cerr << "Entity " << _id << " doesn't exist\n";
		return;
	}
	auto p = entities.find(_parent_id);
	if(p == entities.end()){
		std::cerr << "Parent " << _parent_id << " doesn't exist\n";
		return;
	}
	p->second->addChild(i->second);
}

void EntityGraph::update(){
	{
		mesh_transforms.clear();
		const int reserve_size = hlm::clamp(8, 1024, (int)entities.size() / 4);
		mesh_transforms.reserve(reserve_size);
	}
	for(auto i : root->children){
		update(i, hlm::mat4());
	}
}
void EntityGraph::update(Entity* ent, const hlm::mat4& inmat){
	hlm::mat4 outmat = inmat * ent->transform;
	
	if(ent->hasMesh){
		mesh_transforms.add(outmat, ent->id);
	}
	for(auto a : ent->children){
		update(a, outmat);
	}
}

void EntityGraph::translate(unsigned id, const hlm::vec3& v){
	auto i = entities.find(id);
	if(i == entities.end()){
		std::cerr << "Couldn't find entity " << id << std::endl;
		return;
	}
	i->second->translate(v);
}
void EntityGraph::rotate(unsigned id, const hlm::vec4& v){
	auto i = entities.find(id);
	if(i == entities.end()){
		std::cerr << "Couldn't find entity " << id << std::endl;
		return;
	}
	i->second->rotate(v);
}
void EntityGraph::scale(unsigned id, const hlm::vec3& v){
	auto i = entities.find(id);
	if(i == entities.end()){
		std::cerr << "Couldn't find entity " << id << std::endl;
		return;
	}
	i->second->translate(v);
}
void EntityGraph::setTransform(unsigned id, const Transform& trans){
	auto i = entities.find(id);
	if(i == entities.end()){
		std::cerr << "Couldn't find entity " << id << std::endl;
		return;
	}
	i->second->setTransform(trans);
}