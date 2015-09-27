#include "entitygraph.h"
#include <algorithm>
#include "util.h"

Entity::Entity(const int _id, const int _parent_id, const int _mesh_id, const Transform& trans){
	id = _id;
	mesh_id = _mesh_id;
	parents.insert(_parent_id);
	hlm::mat4 t, r, s;
	t = hlm::translate(trans.translation);
	r = hlm::rotate(trans.angle, trans.rotation);
	s = hlm::scale(trans.scale);
	transform = t * r * s;
}

void EntityGraph::init(const int size){
	entities.reserve(size);
}
void EntityGraph::destroy(){
	entities.clear();
	mesh_transforms.clear();
	root_children.clear();
}
int EntityGraph::insert(const Entity& ent){
	const int parent_id = *ent.parents.begin();
	const int id = ent.id;
	if(entities.find(id) != entities.end()){
		return -1;	//entity already exists
	}
	if(parent_id == 0){
		// entity claims to be child of root
		entities.insert({id, ent});
		root_children.insert(id);
		return id;
	}
	auto parent_iterator = entities.find(parent_id);
	if(parent_iterator == entities.end()){
		// parent doesn't exist
		return -1;
	}
	auto parent = parent_iterator->second;
	if(parent.parents.find(id) != parent.parents.end()){
		return -1;	//cycle
	}
	parent.children.insert(id);
	entities.insert({id, ent});
	return id;
}
void EntityGraph::remove(const int id){
	auto iterator = entities.find(id);
	if(iterator == entities.end()){
		return;// no entity to remove
	}
	std::set<int>& i_children = iterator->second.children;
	for(auto parent_id : iterator->second.parents){
		// to each parent, add your child list so they are not abandoned
		if(parent_id == 0){
			// parent is root
			for(auto child_id : i_children){
				// must remove id from child's parent set, 
				// and add new parent to each child's parent set
				auto child_iterator = entities.find(child_id);
				if(child_iterator != entities.end()){
					auto child = child_iterator->second;
					child.parents.erase(id);
					child.parents.insert(0);
				}
			}
			root_children.insert(i_children.begin(), i_children.end());
			root_children.erase(id);
		}
		else {
			auto parent_iterator = entities.find(parent_id);
			if(parent_iterator != entities.end()){
				for(auto child_id : i_children){
					// must remove id from child's parent set, 
					// and add new parent to each child's parent set
					auto child_iterator = entities.find(child_id);
					if(child_iterator != entities.end()){
						auto child = child_iterator->second;
						child.parents.erase(id);
						child.parents.insert(parent_id);
					}
				}
				// parent is p->second
				std::set<int>& parent_children = parent_iterator->second.children;
				parent_children.insert(i_children.begin(), i_children.end());
				parent_children.erase(id);
			}
		}
	}
	entities.erase(iterator);
}
void EntityGraph::addParent(const int _id, const int _parent_id){
	if(_id == 0){
		return;	// cant make the root a child of anything
	}
	auto i = entities.find(_id);
	if(i == entities.end()){
		return;	// entity doesnt exist
	}
	if(_parent_id == 0){
		root_children.insert(_id);	// parent is root
		i->second.parents.insert(0);
	}
	else {
		auto p = entities.find(_parent_id);
		if(p != entities.end()){
			// parent is an existing node
			auto pparents = p->second.parents;
			if(pparents.find(_id) != pparents.end()){
				return; // cycle
			}
			p->second.children.insert(_id);
			i->second.parents.insert(_parent_id);
		}
	}
}

void EntityGraph::update(){
	{
		mesh_transforms.clear();
		const int reserve_size = std::max(8, (int)(entities.size() / 4));
		mesh_transforms.reserve(reserve_size);
	}
	for(auto i : root_children){
		auto a = entities.find(i);
		if(a != entities.end()){
			update(a->second, hlm::mat4());
		}
	}
}
void EntityGraph::update(const Entity& ent, const hlm::mat4& inmat){
	hlm::mat4 outmat = inmat * ent.transform;
	if(ent.mesh_id != -1){
		// -1 is sentinel flag for being a transform only node
		mesh_transforms.push_back(MeshTransform(ent.mesh_id, outmat));
	}
	for(auto a : ent.children){
		auto b = entities.find(a);
		if(b != entities.end()){
			update(b->second, outmat);
		}
	}
}