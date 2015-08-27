#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "camera.h"
#include "image.h"
#include "GLSLProgram.h"


class Window;
class Input;

class Renderer
{
private:
	Camera m_camera;
	Image fb0, fb1;
	GLSLProgram m_prog;
	Window* m_window;
	Input* m_input;
	GLFWwindow* m_glwindow;

	GLuint m_width, m_height, m_vao, fb0_id, fb1_id;
	

	void bresenhamPass();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
