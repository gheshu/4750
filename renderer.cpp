
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"
#include "objimporter.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "image.h"

using namespace std;
using namespace hlm;

void Renderer::init(const int width, const int height, const int msaa, BoshartParam& param) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "CSC4750");
	m_glwindow = m_window->getWindow();
	m_input = new Input(m_glwindow);
	if(!m_prog.build("shader.vert", "shader.frag")){
		exit(1);
	}
	glViewport(0, 0, m_width, m_height);
}

void Renderer::destroy(){
    delete m_window;
	m_window = nullptr;
	delete m_input;
	m_input = nullptr;
}

void Renderer::draw(BoshartParam& param) {
	LightList lights;
	lights.push_back(Light(param.light_pos));
	MeshList meshes;
	meshes.push_back(Mesh("assets/sphere.obj"));
	meshes[0].setTransform(
		scale(param.s) * rotateEuler(vec4(param.r)) * translate(param.t)
		);
	m_prog.setUniform("model", meshes[0].getTransform());
	{
		mat3 normMat = inverse(transpose(mat3(meshes[0].getTransform())));
		m_prog.setUniform("normMat", normMat);
	}
	ImageList images;
	images.push_back(Image("assets/MoonMap.png"));
	images.push_back(Image("assets/MoonNormal.png"));
	m_prog.setUniformInt("diffuse_tex", 0);
	images[0].bind(0);
	m_prog.setUniformInt("normal_tex", 1);
	images[1].bind(1);
	bindLights(lights, m_prog);
	m_prog.setUniformFloat("spec_exp", param.spec_power);
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
		m_prog.setUniform("eye", cam.getEye());
		{
			mat4 MVP = cam.getVP() * meshes[0].getTransform();
			m_prog.setUniform("MVP", MVP);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		meshes[0].draw();
		glfwSwapBuffers(m_glwindow);
    }
}
