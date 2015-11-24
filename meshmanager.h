#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "mesh.h"
#include "light.h"
#include "hashmap.h"
#include "mat4.h"

class Camera;
class GLSLProgram;
class MaterialManager;

class MeshManager{
	HashMap<unsigned, Mesh> meshes;
public:
	inline void add(unsigned i, const Mesh& m){meshes.add({i, m});}
	inline void remove(unsigned i){meshes.remove(i);}
	inline Mesh* operator[](unsigned i){return meshes[i];}
	inline unsigned size(){return meshes.numItems();}
	void drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights);
	inline void setTransform(unsigned id, hlm::mat4& transform){
		Mesh* i = meshes[id];
		if(i) i->setTransform(transform);
	}
};

#endif