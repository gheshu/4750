#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"

class Window;

class Renderer
{
private:
	Window* m_window;
	GLFWwindow* m_glwindow;

	GLuint m_width, m_height;

	void bresenhamPass();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
