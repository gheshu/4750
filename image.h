#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "vec4.h"

struct Image{
	int width, height;
	unsigned* data = nullptr;
	void init(const int width, const int height);
	void destroy();
	void setPixel(const int x, const int y, unsigned c);
	void clear(unsigned clearColor);
};

#endif