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

struct DrawData{
	hlm::mat4 pw, mv;
	hlm::mat3 norm_mat;
	hlm::vec3 light_pos;
	hlm::vec3 mat, ambient;
	float spec_power;
	float lin_atten;
	Image* texture;
	Image* normal;
	Mesh* mesh;
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
	
	void fillPass(const DrawData& data, const unsigned i);
	void glPass();
	void screenQuadInit();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw(const BoshartParam& param);

};
#endif
