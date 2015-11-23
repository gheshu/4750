#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "glsl_program.h"
#include "window.h"
#include "input.h"
#include "hlm.h"
#include "meshmanager.h"
#include "materialmanager.h"

struct BoshartParam{
	hlm::vec3 t, r, s, mat;
	hlm::vec3 eye, at, up;
	hlm::vec3 light_pos, ambient;
	float fov, near, far, lin_atten, spec_power;
};

class Renderer{
	GLSLProgram m_prog;
	MeshManager mesh_man;
	MaterialManager mat_man;
	Window* m_window;
	GLFWwindow* m_glwindow;
	Input* m_input;
	unsigned m_width, m_height;
public:
    void init(const int width, const int height, const int msaa, BoshartParam& param);
	void destroy();
    void draw(BoshartParam& param);
};
#endif
