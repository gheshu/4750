
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"
#include "objimporter.h"
#include "entitygraph.h"
#include "camera.h"

#ifdef OMP_PARALLEL
	#include "omp.h"
#endif

using namespace std;
using namespace hlm;

void Renderer::init(const int width, const int height, const int msaa, const BoshartParam& param) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "CSC4750");
	m_glwindow = m_window->getWindow();
	m_input = new Input(m_glwindow);
	if(!m_prog.build("shader.vert", "shader.frag")){
		exit(1);
	}
	glViewport(0, 0, m_width, m_height);
	mesh_man.add("assets/sphere.obj", "moon", "sphere");
	mat_man.addTexture("assets/MoonMap.png", "moon");
	mat_man.addNormal("assets/MoonNormal.png", "moon");
	mat_man.addMaterial("moon", Material("moon", "moon", param.spec_power));
}

void Renderer::destroy(){
	mat_man.clear();
	mesh_man.clear();
    delete m_window;
	m_window = nullptr;
	delete m_input;
	m_input = nullptr;
}

void Renderer::draw(const BoshartParam& param) {
	EntityGraph graph;
	graph.init(1);
	{
		Transform t;
		t.add(T, param.t);
		t.add(R, param.r);
		t.add(S, param.s);
		graph.insert("sphere", "root", true, t);
		graph.update();
	}
	TransformList* instance_xforms = graph.getTransforms();
	mesh_man.setTransforms(*instance_xforms);
	LightList lights;
	lights.push_back(Light(param.light_pos));
	const double ratio = (double)m_width / (double)m_height;
	Camera cam;
	cam.init(param.eye, param.at, param.up, param.fov, ratio, param.near, param.far);
	m_prog.setUniform("ambient", param.ambient);

	m_prog.bind();
	glfwSetTime(0.0);
	unsigned frame_i = 0;
	double dtavg = 0.0;
    while (!glfwWindowShouldClose(m_glwindow)) {
		// update frame time
		double dt = glfwGetTime();
		glfwSetTime(0.0);
		dtavg += dt;
		frame_i++;
		if(frame_i % 60 == 0){
			printf("FPS: %f\n", 60.0 / dtavg);
			dtavg = 0.0;
		}
		
		// update camera and poll glfw events
		m_input->poll(dt, cam);
		if(glfwGetKey(m_glwindow, GLFW_KEY_R)){
			cam.init(param.eye, param.at, param.up, param.fov, ratio, param.near, param.far);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh_man.drawAll(m_prog, mat_man, cam, lights);
		glfwSwapBuffers(m_glwindow);
    }
	//---------end draw loop--------------------------------
	instance_xforms = nullptr;
	graph.destroy();
}
