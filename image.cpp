#include "image.h"
#include <string>
#include <algorithm>
#include "vec3.h"
#include "vec4.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Image::loadFile(const std::string& filename){
	if (data != nullptr){
		return;
	}
	int n;
	data = stbi_load(filename.c_str(), &width, &height, &n, 4);
	if (!data){
		printf("image %s could not be loaded\n", filename.c_str());
		return;
	}
	length = width * height * 4;
}

void Image::unloadFile(){
	stbi_image_free(data);
	data = nullptr;	
}

void Image::init(const int _width, const int _height){
	if(data != nullptr){return;}
	width = _width; height = _height;
	length = width * height * 4;
	data = (uint_8*)malloc(sizeof(uint_8) * length);
}

void Image::destroy(){
	free(data);
	data = nullptr;
}

void Image::setPixel(const hlm::vec4& pos, const hlm::vec3& color){
	uint_8* i = (data + (int)pos.x * 4 + (int)pos.y * width * 4);
	*i = (uint_8)(255 * color.x);
	*(i+1) = (uint_8)(255 * color.y);
	*(i+2) = (uint_8)(255 * color.z);
	*(i+3)= 255;
}

hlm::vec3 Image::texelW(const hlm::vec3& pos){
	const int x = fmod(abs(pos.x), 1.0f) * (width  - 1);
	const int y = fmod(abs(pos.y), 1.0f) * (height - 1);
	uint_8* i = (data + x*4 + y*4*width);
	return hlm::vec3(*i / 255.0f, *(i+1) / 255.0f, *(i+2) / 255.0f);
}

void Image::clear(){
	for(int i = 0; i < length; i++){
		*(data + i) = 0;
	}
}
