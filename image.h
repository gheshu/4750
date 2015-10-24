#ifndef IMAGE_H
#define IMAGE_H

typedef unsigned char uint_8;
namespace hlm{
	class vec3;
	class vec4;
};

struct Pixel{
	uint_8 r, g, b, a;
	Pixel(const uint_8 _r, const uint_8 _g, const uint_8 _b, const uint_8 _a) 
		: r(_r), g(_g), b(_b), a(_a){};
};

struct Image{
	int width, height;
	Pixel* data = nullptr;
	void init(const int width, const int height);
	void destroy();
	void setPixel(int x, int y, const Pixel& p);
	void setPixel(int x, int y, const hlm::vec3& color);
	void setPixel(const hlm::vec4& pos, const hlm::vec3& color);
	void orPixel(int x, int y, const Pixel& p);
	void clear(const Pixel& p);
	void clear();
};

#endif