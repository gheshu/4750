#include "depthbuffer.h"

#include "vec3.h"

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
	if(x >= width){
		return NEAR;
	}
	if(y >= height){
		return NEAR;
	}
	return *(data + x + y*width);
}
bool DepthBuffer::set(const unsigned x, const unsigned y, const float val){
	if(x >= width){
		return false;
	}
	if(y >= height){
		return false;
	}
	float *i = (data + x + y * width);
	if(val > NEAR || val < *i){
		return false;
	}
	*i = val;
	return true;
}
bool DepthBuffer::set(const hlm::vec3& v){
	if(v.x >= width){
		return false;
	}
	if(v.y >= height){
		return false;
	}
	float *i = (data + (int)v.x + (int)v.y * width);
	if(v.z > NEAR || v.z < *i){
		return false;
	}
	*i = v.z;
	return true;
}
void DepthBuffer::clear(){
	for(unsigned i = 0; i < width * height; i++){
		*(data + i) = FAR;
	}
}