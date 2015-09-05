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
	if(x >= width || x < 0 || y >= height || y < 0){ return; }
	*(data + x + y * width) = p;
}

void Image::clear(const Pixel& p){
	for(int i = 0; i < width * height; i++){
		*(data + i) = p;
	}
}