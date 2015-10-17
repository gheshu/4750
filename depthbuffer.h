#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#define FAR -1.0
#define NEAR 1.0

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
		clear();
	}
	inline void destroy(){
		free(data);
		data = nullptr;
	}
	inline double get(const unsigned x, const unsigned y){
		if(x >= width){
			return NEAR;
		}
		if(y >= height){
			return NEAR;
		}
		return *(data + x + y*width);
	}
	inline bool set(const unsigned x, const unsigned y, const double val){
		if(x >= width){
			return false;
		}
		if(y >= height){
			return false;
		}
		double *i = (data + x + y * width);
		if(val > NEAR || val < *i){
			return false;
		}
		*i = val;
		return true;
	}
	inline void clear(){
		for(unsigned i = 0; i < width * height; i++){
			*(data + i) = FAR;
		}
	}
};

#endif