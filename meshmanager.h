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
	Manager<Mesh> meshes;
public:
	inline void add(const Mesh& mesh, unsigned id){meshes.add(mesh, id);}
	inline Mesh* get(const unsigned i){return meshes.get(i);}
	inline void remove(const unsigned i){meshes.remove(i);
	inline void sort(){meshes.sort();}
	inline void clear(){meshes.clear();}
	inline void reserve(unsigned i){meshes.reserve(i);}
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