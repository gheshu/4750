#include "depthbuffer.h"

#include "vec3.h"
#include "vec4.h"

#define FAR -1.0
#define NEAR 1.0

void DepthBuffer::init(const unsigned _width, const unsigned _height){
	if(data != nullptr){
		return;
	}
	width = _width; height = _height;
	data = new float[width * height];
	clear();
}
void DepthBuffer::destroy(){
	delete[] data;
	data = nullptr;
}
float DepthBuffer::get(const unsigned x, const unsigned y){
	return *(data + x + y*width);
}

bool DepthBuffer::top(const hlm::vec4& v){
	if(v.x < 0.0f || v.x >= width){
		return false;
	}
	if(v.y < 0.0f || v.y >= height){
		return false;
	}
	if(v.z > NEAR || v.z < *(data + (int)v.x + (int)v.y * width)){
		return false;
	}
	return true;
}

void DepthBuffer::set(const hlm::vec4& v){
	*(data + (int)v.x + (int)v.y * width) = v.z;
}
void DepthBuffer::clear(){
	for(unsigned i = 0; i < width * height; i++){
		*(data + i) = FAR;
	}
}