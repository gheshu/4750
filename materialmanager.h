#ifndef MAT_MANAGER_H
#define MAT_MANAGER_H

#include "manager.h"
#include "image.h"
#include "material.h"

class GLSLProgram;

class MaterialManager{
	Manager<Image> images;
	Manager<Material> materials;
public:
	inline void addImage(const Image& img, unsigned id){images.add(img, id);}
	inline void addMaterial(const Material& mat, unsigned id){materials.add(mat, id);}
	inline Image* getImage(unsigned id){ return images.get(id);}
	inline Material* getMaterial(unsigned id){return materials.get(id);}
	inline void removeImage(unsigned id){images.remove(id);}
	inline void removeMaterial(unsigned id){materials.remove(id);}
	inline void sortImages(){images.sort();}
	inline void sortMaterials(){materials.sort();}
	inline void sort(){sortImages(); sortMaterials();}
	inline void clearImages(){images.clear();}
	inline void clearMaterials(){materials.clear();}
	inline void clear(){clearImages(); clearMaterials();}
	inline void reserveImages(unsigned i){images.reserve(i);}
	inline void reserveMaterials(unsigned i){materials.reserve(i);}
	inline void reserve(unsigned i){reserveImages(i); reserveMaterials(i);}
	void bindMaterial(unsigned id, GLSLProgram& prog);
};

#endif