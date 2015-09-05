#ifndef IMAGE_H
#define IMAGE_H

typedef unsigned char uint_8;

struct Pixel{
	uint_8 r, g, b, a;
	Pixel(uint_8 _r, uint_8 _g, uint_8 _b, uint_8 _a) 
		: r(_r), g(_g), b(_b), a(_a){};
};

struct Image{
	int width, height;
	Pixel* data = nullptr;
	void init(const int width, const int height);
	void destroy();
	void setPixel(const int x, const int y, const Pixel& p);
	void clear(const Pixel& p);
};

#endif