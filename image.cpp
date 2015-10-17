#include "image.h"
#include <string>
#include <algorithm>
#include "vec3.h"

void Image::init(const int _width, const int _height){
	if(data != nullptr){return;}
	width = _width; height = _height;
	data = (Pixel*)malloc(sizeof(Pixel) * width * height);
}

void Image::destroy(){
	free(data);
	data = nullptr;
}

void Image::setPixel(int x, int y, const Pixel& p){
	if(x > width-1 || x < 0){
		return;
	}
	if(y > height-1 || y < 0){
		return;
	}
	*(data + x + y * width) = p;
}

void Image::setPixel(int x, int y, const hlm::vec3& v){
	Pixel *i = (data + x + y * width);
	i->r = (uint_8)(255 * v.x);
	i->g = (uint_8)(255 * v.y);
	i->b = (uint_8)(255 * v.z);
	i->a = 255;
}

void Image::setPixel(const hlm::vec3& pos, const hlm::vec3& color){
	Pixel *i = (data + (int)pos.x + (int)pos.y * width);
	i->r = (uint_8)(255 * color.x);
	i->g = (uint_8)(255 * color.y);
	i->b = (uint_8)(255 * color.z);
	i->a = 255;
}

void Image::orPixel(int x, int y, const Pixel& p){
	x = std::min(width - 1, std::max(0, x));
	y = std::min(height - 1, std::max(0, y));
	Pixel* i = (data + x + y * width);
	i->r |= p.r;
	i->g |= p.g;
	i->b |= p.b;
	i->a |= p.a;
}

void Image::clear(const Pixel& p){
	for(int i = 0; i < width * height; i++){
		*(data + i) = p;
	}
}
