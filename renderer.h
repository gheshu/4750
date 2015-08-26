#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"

class Window;
class Input;

class Renderer
{
private:
	Window* m_window;
	Input* m_input;
	GLFWwindow* m_glwindow;

	GLuint m_width, m_height;

	void bresenhamPass();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
