#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "mesh.h"
#include <string>
#include <unordered_map>

class ResourceManager{
	std::unordered_map<std::string, Mesh> keys;
public:
	void init(const unsigned size);
	void destroy();
	void insert(const std::string& name, const Mesh& item);
	void remove(const std::string& name);
	Mesh* get(const std::string& name);
	void load(const std::string& filename, const std::string& name);
	void loadNoIndices(const std::string& filename, const std::string& name, bool smooth, bool project);
};

#endif