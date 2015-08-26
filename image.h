#ifndef IMAGE_H
#define IMAGE_H

#include <string>

struct Image{
	int width, height, n;
	// n is number of components per pixel ie: r = 1, rg = 2, rgb = 3, rgba = 4
	unsigned char* data = nullptr;
	void load(const std::string& filename);
	void unload();
};

#endif