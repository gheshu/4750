#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "image.h"
#include "glsl_program.h"
#include "window.h"
#include "input.h"
#include "hlm.h"
#include "vertexbuffer.h"
#include "resourcemanager.h"
#include "camera.h"

class Renderer
{
private:
	Camera m_camera;
	GLSLProgram m_prog;
	Image fb;
	ResourceManager res_man;
	Window* m_window;
	GLFWwindow* m_glwindow;
	Input* m_input;

	GLuint m_width, m_height, m_vao;
	GLuint fb_id;
	float m_fov;
	
	void DDAPass(const hlm::mat4& proj, const VertexBuffer& verts, Image& img);
	void glPass(const Image& img, const GLuint vao, const GLuint fb_id);
	void screenQuadInit(GLuint& vao, GLuint& id0);
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
