#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "vec4.h"

struct Image{
	int width, height, n;
	// n is number of components per pixel ie: r = 1, rg = 2, rgb = 3, rgba = 4
	unsigned* data = nullptr;
	void init(const int width, const int height);
	void destroy();
	void setPixel(const int x, const int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void setPixel(const int x, const int y, const vec4& color);
};

#endif