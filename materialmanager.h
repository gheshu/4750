#ifndef MAT_MANAGER_H
#define MAT_MANAGER_H

#include "manager.h"
#include "image.h"
#include "material.h"

class GLSLProgram;

class MaterialManager{
	Manager<unsigned, Image> images;
	Manager<unsigned, Material> materials;
public:
	inline void add(unsigned id, const Image& img){images.add(id, img);}
	inline void add(unsigned id, const Material& mat){materials.add(id, mat);}
	inline Image* getImage(unsigned id){ return images.get(id);}
	inline Material* getMaterial(unsigned id){return materials.get(id);}
	inline void removeImage(unsigned id){images.remove(id);}
	inline void removeMaterial(unsigned id){materials.remove(id);}
	inline void clear(){images.clear(); materials.clear();}
	inline void reserveImages(unsigned i){images.reserve(i);}
	inline void reserveMaterials(unsigned i){materials.reserve(i);}
	void bindMaterial(unsigned id, GLSLProgram& prog);
};

#endif