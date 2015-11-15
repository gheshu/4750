#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <cstring>	// memset

typedef unsigned char uint_8;
namespace hlm{
	class vec2;
	class vec3;
	class vec4;
};

struct Image{
	int width, height, length;
	uint_8* data = nullptr;
	void init(const int width, const int height);
	void loadFile(const std::string& filename);
	void unloadFile();
	inline void destroy(){ free(data); data = nullptr; }
	void setPixel(const hlm::vec4& pos, const hlm::vec3& color);
	hlm::vec3 texelW(const hlm::vec2& pos);
	inline void clear(){ memset(data, 0, length); }
};

#endif