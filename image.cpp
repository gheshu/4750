#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void Image::load(const std::string& filename){
	if (data != nullptr){
		return;
	}
	data = stbi_load(filename.c_str(), &width, &height, &n, 3);
	if (!data){
		printf("image %s could not be loaded\n", filename.c_str());
	}
}
void Image::unload(){
	stbi_image_free(data);
	data = nullptr;
}