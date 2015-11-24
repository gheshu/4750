#ifndef MAT_MANAGER_H
#define MAT_MANAGER_H

#include "hashmap.h"
#include "image.h"
#include "material.h"

class GLSLProgram;

class MaterialManager{
	HashMap<unsigned, Image> images;
	HashMap<unsigned, Material> materials;
public:
	inline void add(unsigned id, const Image& img){images.add({id, img});}
	inline void add(unsigned id, const Material& mat){materials.add({id, mat});}
	inline Image* getImage(unsigned id){ return images[id];}
	inline Material* getMaterial(unsigned id){return materials[id];}
	inline void removeImage(unsigned id){images.remove(id);}
	inline void removeMaterial(unsigned id){materials.remove(id);}
	void bindMaterial(unsigned id, GLSLProgram& prog);
};

#endif