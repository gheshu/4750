#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

class DepthBuffer{
	double* data = nullptr;
public:
	inline void init(const unsigned width, const unsigned height){
		if(data != nullptr){
			return;
		}
		data = (double*)malloc(sizeof(double) * width * height);
		for(unsigned i = 0; i < width * height; i++){
			*(data + i) = -1.0;
		}
	}
	inline void destroy(){
		free(data);
		data = nullptr;
	}
	inline double get(const unsigned x, const unsigned y){
		if(x >= width){
			return 1.0;
		}
		if(y >= height){
			return 1.0;
		}
		return *(data + x + y*width);
	}
	inline void set(const unsigned x, const unsigned y, const double val){
		if(x >= width){
			return;
		}
		if(y >= height){
			return;
		}
		*(data + x + y * width) = val;
	}
};

#endif