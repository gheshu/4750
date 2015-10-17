#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "image.h"
#include "glsl_program.h"
#include "window.h"
#include "input.h"
#include "hlm.h"
#include "mesh.h"
#include "resourcemanager.h"
#include "camera.h"
#include "depthbuffer.h"

struct BoshartParam{
	hlm::vec3 t, r, s;
	hlm::vec3 eye, at, up;
	float fov, near, far;
};

class Renderer
{
private:
	GLSLProgram m_prog;
	Image framebuffer;
	DepthBuffer depthbuffer;
	ResourceManager res_man;
	Window* m_window;
	GLFWwindow* m_glwindow;
	Input* m_input;

	GLuint m_width, m_height, m_vao;
	GLuint fb_id;
	
	void parFillPass(const hlm::mat4& proj, Mesh* mesh, const unsigned i);
	void fillPass(const hlm::mat4& proj, Mesh* mesh);
	void DDAPass(const hlm::mat4& proj, Mesh* verts);
	void glPass();
	void screenQuadInit();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw(const BoshartParam& param);

};
#endif
