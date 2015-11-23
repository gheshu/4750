#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "mesh.h"
#include "objimporter.h"
#include "instancetransform.h"
#include "light.h"
#include "manager.h"

class Camera;
class GLSLProgram;
class MaterialManager;

class MeshManager{
public:
	Manager<Mesh> meshes;
	void drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights);
	inline void setTransforms(InstanceList& list){
		list.sort();
		meshes.sort();
		for(auto i : list){
			Mesh* m = get(i.id);
			if(m) m->setTransform(i.item);
		}
	}
};

#endif