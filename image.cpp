#include "image.h"

void Image::init(const int _width, const int _height){
	if(data != nullptr){return;}
	width = _width; height = _height;
	data = new unsigned [width * height];
}

void Image::destroy(){
	delete data;
	data = nullptr;
}

void Image::setPixel(const int x, const int y, unsigned c){
	if(x >= width || x < 0 || y >= height || y < 0){ return; }
	*(data + x + y * width) = c;
}