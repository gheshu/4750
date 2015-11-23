#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "mesh.h"
#include "objimporter.h"
#include <string>
#include <unordered_map>
#include "instancetransform.h"
#include "light.h"

class Camera;
class GLSLProgram;
class MaterialManager;

class MeshManager{
	std::unordered_map<std::string, Mesh> meshes;
public:
	inline void add(const std::string& filename, const std::string& material, const std::string& mesh_name){
		meshes.insert({mesh_name, Mesh(filename, material)});
		}
	inline void remove(const std::string& name){meshes.erase(name);}
	inline void clear(){meshes.clear();}
	void drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights);
	inline void setTransforms(const TransformList& list){for(auto i:list)meshes[i.first].setTransform(i.second);}
};

#endif