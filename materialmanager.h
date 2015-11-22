#ifndef MAT_MANAGER_H
#define MAT_MANAGER_H

#include <unordered_map>
#include <string>
#include "image.h"
#include "material.h"

class GLSLProgram;

class MaterialManager{
	std::unordered_map<std::string, Image> textures, normals;
	std::unordered_map<std::string, Material> materials;
	inline void addTexture(const std::string& filename, const std::string& name){textures.insert({name, Image(name)});}
	inline void addNormal(const std::string& filename, const std::string& name){normals.insert({name, Image(name)});}
	inline void addMaterial(const std::string& name, const std::Material& mat){materials.insert({name, mat});}
	inline void removeTexture(const std::string& name){textures.remove(name);}
	inline void removeNormal(const std::string& name){normals.remove(name);}
	inline void removeMaterial(const std::string& name){materials.remove(name);}
	inline void clear(){textures.clear(); normals.clear(); materials.clear();}
	void bindMaterial(const std::string& name, GLSLProgram& prog);
};

#endif