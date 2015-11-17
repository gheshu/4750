#include "image.h"
#include <string>
#include <algorithm>
#include "hlm.h"

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
		data = nullptr;
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

void Image::setPixel(const hlm::vec4& pos, const hlm::vec3& color){
	uint_8* i = (data + (int)pos.x * 4 + (int)pos.y * width * 4);
	*i = (uint_8)(255 * color.x);
	*(i+1) = (uint_8)(255 * color.y);
	*(i+2) = (uint_8)(255 * color.z);
	*(i+3)= 255;
}

// dont pass things larger than 512 as uv coords
hlm::vec3 Image::texelW(const hlm::vec2& pos){
	const int x = modf(-pos.x + 512.0f, nullptr)*(width-1);
	const int y = modf(-pos.y + 512.0f, nullptr)*(height-1);
	uint_8* i = (data + x*4 + y*4*width);
	return hlm::vec3(*i / 255.0f, *(i+1) / 255.0f, *(i+2) / 255.0f);
}
