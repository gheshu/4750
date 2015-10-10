#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

class DepthBuffer{
	double* data = nullptr;
	unsigned width, height;
public:
	inline void init(const unsigned _width, const unsigned _height){
		if(data != nullptr){
			return;
		}
		width = _width; height = _height;
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
	inline void clear(){
		for(unsigned i = 0; i < width * height; i++){
			*(data + i) = -1.0;
		}
	}
};

#endif