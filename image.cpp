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

void Image::setPixel(const int x, const int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	unsigned value = r;
	value <<= 8;
	value |= g;
	value <<= 8;
	value |= b;
	value <<= 8;
	value |= a;
	*(data + x + y * width) = value;
}

void Image::setPixel(const int x, const int y, const vec4& color){
	vec4 c = color;
	normalize(c);
	unsigned char r = floor(c.x * 255.0f);
	unsigned char g = floor(c.y * 255.0f);
	unsigned char b = floor(c.z * 255.0f);
	unsigned char a = floor(c.w * 255.0f);
	
	unsigned value = r;
	value <<= 8;
	value |= g;
	value <<= 8;
	value |= b;
	value <<= 8;
	value |= a;
	*(data + x + y * width) = value;
}