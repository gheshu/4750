#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "mesh.h"
#include <string>

class ResourceManager{
	std::unordered_map<std::string, Mesh> keys;
public:
	void init(const unsigned size);
	void destroy();
	void insert(const string& name, const Mesh& item);
	void remove(const string& name);
	Mesh* get(const string& name);
	void load(const string& filename);
};

#endif