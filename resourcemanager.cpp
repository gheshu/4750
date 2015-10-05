#include "resourcemanager.h"

void ResourceManager::init(const unsigned size){
	keys.reserve(size);
}
void ResourceManager::destroy(){
	keys.clear();
}
void ResourceManager::insert(const string& name, const Mesh& item){
	keys.insert({name, item});
}
void ResourceManager::remove(const string& name){
	keys.erase(name);
}
void ResourceManager::load(const string& path, const string& name){
	Mesh m;
	std::string fullpath = path;
	for( char* i : fullpath){
		if( *i == '\\'){
			*i = '/';
		}
	}
	if(fullpath.back() != '/')
		fullpath.push_back('/');
	}
	fullpath.push_back(name);
	if(objload(fullpath, m)){
		keys.insert({name, m});
	}
}

Mesh* ResourceManager::get(const string& name){
	auto a = keys.find(name);
	if(a->second == keys.end()){
		return nullptr;
	}
	return a->second;
}