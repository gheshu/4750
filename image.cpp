#include "image.h"
#include <string>

void Image::init(const int _width, const int _height){
	if(data != nullptr){return;}
	width = _width; height = _height;
	data = (Pixel*)malloc(sizeof(Pixel) * width * height);
}

void Image::destroy(){
	free(data);
	data = nullptr;
}

void Image::setPixel(const int x, const int y, const Pixel& p){
	x = std::min(width - 1, std::max(0, x));
	y = std::min(height - 1, std::max(0, y));
	*(data + x + y * width) = p;
}

void Image::orPixel(const int x, const int y, const Pixel& p){
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
