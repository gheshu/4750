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
	hlm::vec3 t, r, s, mat;
	hlm::vec3 eye, at, up;
	hlm::vec3 light_pos, ambient;
	float fov, near, far, lin_atten, spec_power;
};

class Renderer
{
private:
	hlm::mat4 m_wmatrix;
	BoshartParam m_param;
	hlm::vec3 m_light_pos;
	GLSLProgram m_prog;
	Image framebuffer;
	DepthBuffer depthbuffer;
	ResourceManager res_man;
	Window* m_window;
	GLFWwindow* m_glwindow;
	Input* m_input;

	GLuint m_width, m_height, m_vao;
	GLuint fb_id;
	
	
	
	void fillPass(const hlm::mat4& proj, Mesh* mesh, const unsigned i);
	void glPass();
	void screenQuadInit();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw(const BoshartParam& param);

};
#endif
