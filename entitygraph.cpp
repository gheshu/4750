#include "entitygraph.h"
#include <vector>

Entity::Entity(int _id, int _mesh_id, int _parent_id, const Transform& trans){
	id = _id;
	mesh_id = _mesh_id;
	parent_id = _parent_id;
	hlm::mat4 t, r, s;
	t = hlm::translate(trans.translation);
	r = hlm::rotate(trans.angle, trans.rotation);
	s = hlm::scale(trans.scale);
	transform = t * r * s;
}

void EntityGraph::init(int size){
	entities.reserve(size);
}
void EntityGraph::destroy(){
	root_children.clear();
	entities.clear();
}
int EntityGraph::insert(const Entity& ent){
	const int parent = ent.parent_id;
	const int id = ent.id;
	if(entities.find(id) == entities.end()){
		return -1;	//entity already exists
	}
	if(parent == 0){
		// entity claims to be child of root
		entities.insert({id, ent});
		root_children.insert(id);
		return id;
	}
	auto i = entities.find(parent);
	if(i == entities.end()){
		// parent doesn't exist
		return -1;
	}
	i->second.children.insert(id);
	entities.insert({id, ent});
	return id;
}
void EntityGraph::remove(int id){
	auto i = entities.find(id);
	if(i == entities.end()){
		return;// no entity to remove
	}
	int parent_id = i->second.parent_id;
	auto p = entities.find(parent_id);
	auto c = i->second.children;
	if(p == entities.end()){
		// parent is root
		root_children.insert(c.begin(), c.end());
		entities.erase(i);
		return;
	}
	// parent is p->second
	p->second.children.insert(c.begin(), c.end());
	entities.erase(i);
}
void EntityGraph::getWorldTransform(int id, hlm::mat4& out_mat){
	int cur_id = id;
	std::vector<hlm::mat4*> transforms;
	while(cur_id != 0){
		auto i = entities.find(cur_id);
		if(i == entities.end()){
			break;
		}
		transforms.push_back(&(i->second.transform));
		cur_id = i->second.parent_id;
	}
	// one of these ought to be right :P
#if 1
	for(int i = transforms.size() - 1; i > 0; i--){
		out_mat = out_mat * *transforms[i];
	}
#else
	for(int i = 0; i < transforms.size(); i++){
		out_mat = out_mat * *transforms[i];
	}
#endif
}