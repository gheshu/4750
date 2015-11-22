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
	std::unordered_map<std::string, MeshData> mesh_data;
	std::unordered_map<std::string, Mesh> meshes;
	inline void addData(const std::string& filename, const std::string& name){
		MeshData data;
		if(objload(filename, data)){
			mesh_data.insert({name, data});
		}
	}
	inline void addMesh(Mesh& mesh, const std::string& mesh_name, const std::string& data_name){
		mesh.setMeshData(mesh_data[data_name]);
		meshes.insert({mesh_name, mesh});
	}
	inline void remove(const std::string& name){mesh_data.remove(name);}
	inline void destroy(){mesh_data.clear();}
	void drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights);
	inline void setTransforms(const TransformList& list){for(auto i:list)meshes[i.first].setTransform(i.second);}
};

#endif