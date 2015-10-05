#include "resourcemanager.h"
#include "objimporter.h"

void ResourceManager::init(const unsigned size){
	keys.reserve(size);
}
void ResourceManager::destroy(){
	keys.clear();
}
void ResourceManager::insert(const std::string& name, const Mesh& item){
	keys.insert({name, item});
}
void ResourceManager::remove(const std::string& name){
	keys.erase(name);
}
void ResourceManager::load(const std::string& filename, const std::string& name){
	Mesh m;
	if(objload(filename, m)){
		keys.insert({name, m});
	}
}

Mesh* ResourceManager::get(const std::string& name){
	auto a = keys.find(name);
	if(a == keys.end()){
		return nullptr;
	}
	return &(a->second);
}