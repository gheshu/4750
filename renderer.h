#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "image.h"
#include "glsl_program.h"
#include "window.h"
#include "input.h"
#include "hlm.h"

typedef vector<vec4> VertexBuffer;
typedef vector<int> IndexBuffer;

class Renderer
{
private:
	GLSLProgram m_prog;
	Image fbs[2];
	Window* m_window;
	GLFWwindow* m_glwindow;
	Input* m_input;

	GLuint m_width, m_height, m_vao;
	GLuint fb_ids[2];
	
	void bresenhamPass();
	void DDAPass();
	void glPass();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
