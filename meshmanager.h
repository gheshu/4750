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
	Manager<unsigned, Mesh> meshes;
public:
	inline void add(unsigned i, const Mesh& m){meshes.add(i, m);}
	inline void remove(unsigned i){meshes.remove(i);}
	inline Mesh* operator[](unsigned i){return &meshes[i]->value;}
	inline Mesh* get(unsigned i){return meshes.get(i);}
	inline unsigned size(){return meshes.size();}
	inline void reserve(unsigned i){meshes.reserve(i);}
	inline void clear(){meshes.clear();}
	void drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights);
	inline void setTransforms(TransformList* list){
		list->sort();
		for(unsigned i = 0; i < list->size(); i++){
			Pair<unsigned, hlm::mat4>* item = (*list)[i];
			Mesh* m = get(item->key);
			if(m) m->setTransform(item->value);
		}
	}
};

#endif