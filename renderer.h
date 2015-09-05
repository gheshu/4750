#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "image.h"
#include "glsl_program.h"
#include "window.h"
#include "input.h"
#include "hlm.h"
#include "vertexbuffer.h"

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
	
	void bresenhamPass(hlm::mat4& proj, VertexBuffer& verts, Image& img);
	void DDAPass(hlm::mat4& proj, VertexBuffer& verts, Image& img);
	void glPass(Image& img, GLuint& vao, GLuint& fb_id);
	void screenQuadInit(GLuint& vao, GLuint& id0, GLuint& id1);
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
