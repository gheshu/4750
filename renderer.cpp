
#include "renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "debugmacro.h"
#include "image.h"
#include "texture.h"
#include "scriptmanager.h"
#include "light.h"
#include "input.h"
#include "window.h"

#include <algorithm>

using namespace std;

void Renderer::destroy() {
	for (auto i : m_meshes){
		i.destroy();
	}
	for (auto i : m_lights){
		i.destroy();
	}
	for (auto i : m_textures){
		i.destroy();
	}
	delete m_input;
	m_input = nullptr;
    delete m_window;
	m_window = nullptr;
}

void Renderer::init(const int width, const int height, const int msaa) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "Vroom");
	m_glwindow = m_window->getWindow();
	m_input = new Input(m_glwindow, &m_camera);

	m_camera.init(60.0f, (float)width / (float)height, 0.1f, 10.0f, glm::vec3(-1.0f, 1.0f, -1.0f));

	if (!m_program.build("shaders/shader.vert", "shaders/shader.frag") || 
		!shadow_program.build("shaders/shadow.vert", "shaders/shadow.frag") ||
		!omni_shadow_program.build("shaders/omnishadow.vert", "shaders/omnishadow.geom", "shaders/omnishadow.frag")){
		std::cin.ignore();
		exit(1);
	}
	ScriptManager scrip_man;

	m_meshes.push_back(Mesh());
	m_meshes[0].initialise(0);
	m_meshes[0].loadFromFile("assets/test.fbx");
	m_meshes[0].rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	std::sort(m_meshes.begin(), m_meshes.end());

	m_textures.push_back(Texture());
	m_textures.push_back(Texture());
	m_textures[0].init();
	m_textures[0].uploadFromFile("assets/d_stuff.png");
	m_textures[1].init();
	m_textures[1].uploadFromFile("assets/n_stuff.png");

	m_lights.push_back(Light());
	m_lights[0].init(DIRECTIONAL, glm::vec3(-1.0f, 1.0f, -1.0f));
	std::sort(m_lights.begin(), m_lights.end());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	MYGLERRORMACRO

	depthPassInit();
}

void Renderer::depthPassInit(){
	SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
	// ------------------------ directional DEPTHMAP setup ------------------
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	MYGLERRORMACRO
	 // ------------------------------------- CUBEMAP -----------------------
	 /*
	glGenFramebuffers(1, &depthCubeFBO);
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (GLuint i = 0; i < 6; ++i){
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindFramebuffer(GL_FRAMEBUFFER, depthCubeFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	MYGLERRORMACRO
	*/
}

void Renderer::pointGLPass(Light* light){
	// ==================== depth pass ======================
	//glCullFace(GL_FRONT);
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthCubeFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	omni_shadow_program.bind();
	omni_shadow_program.setUniform("lightPos", *light->getPosition());
	omni_shadow_program.setUniformFloat("far_plane", light->getFarPlane());
	glm::mat4* mat = light->getVPMat();
	for (GLuint i = 0; i < 6; i++){
		omni_shadow_program.setUniform(std::string("shadowMatrices[" + std::to_string(i) + "]"), 
			*(mat + i));
	}
	for (auto i : m_meshes){
		omni_shadow_program.setUniform("model", *i.getMatrix());
		i.draw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCullFace(GL_BACK);

	// ====================== base pass ======================

	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_program.bind();
	glm::mat4* VP = m_camera.getVPMat();
	//set depth map to channel 3
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	m_program.setUniformInt("depthCube", 3);
	m_program.setUniform("cameraPos", *m_camera.getPosition());
	// setup light uniforms
	m_program.setUniform("lightPos", *light->getPosition());
	m_program.setUniform("lightColor", *light->getColor());
	m_program.setUniformFloat("ambient", 0.01f);
	m_program.setUniformInt("directional", 0);
	for (auto i : m_meshes){
		glm::mat4* model = i.getMatrix();
		glm::mat4 MVP = *VP * *model;
		// setup material settings for this mesh
		m_program.setUniformFloat("specularity", 1.0f);
		m_program.setUniformInt("shininess", 64);
		// set diffuse on channel 0, normal on channel 1
		m_textures[0].bind(0);
		m_program.setUniformInt("diffuse_tex", 0);
		m_textures[1].bind(1);
		m_program.setUniformInt("normal_tex", 1);
		m_program.setUniform("MVP", MVP);
		glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(*model)));
		m_program.setUniform("normMat", normMat);
		i.draw();
	}
}

void Renderer::directionalGLPass(Light* light) {
	// ==================== depth pass ======================
	//glCullFace(GL_FRONT);
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	shadow_program.bind();
	for (auto i : m_meshes){
		glm::mat4 LSM = *light->getVPMat() * *i.getMatrix();
		shadow_program.setUniform("LSM", LSM);
		i.draw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCullFace(GL_BACK);

	// ================== base pass ==================

	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_program.bind();
	//set depth map to channel 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	m_program.setUniformInt("depthMap", 2);
	m_program.setUniform("cameraPos", *m_camera.getPosition());
	// setup light uniforms
	m_program.setUniform("lightPos", *light->getPosition());
	m_program.setUniform("lightColor", *light->getColor());
	m_program.setUniformFloat("ambient", 0.01f);
	m_program.setUniformInt("directional", 1);
	glm::mat4* VP = m_camera.getVPMat();
	for (auto i : m_meshes){
		// setup matrices
		glm::mat4* model = i.getMatrix();
		m_program.setUniform("model", *model);
		glm::mat4 MVP = *VP * *model;
		m_program.setUniform("MVP", MVP);
		glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(*model)));
		m_program.setUniform("normMat", normMat);
		m_program.setUniform("lightSpaceMatrix", *light->getVPMat());
		// setup material settings for this mesh
		m_program.setUniformFloat("specularity", 1.0f);
		m_program.setUniformInt("shininess", 64);
		// set diffuse on channel 0, normal on channel 1
		m_textures[0].bind(0);
		m_program.setUniformInt("diffuse_tex", 0);
		m_textures[1].bind(1);
		m_program.setUniformInt("normal_tex", 1);
		i.draw();
	}
}

void Renderer::draw() {
	float avg_rate = 0.0f;
	unsigned frame_counter = 0;
    while (!glfwWindowShouldClose(m_glwindow)) {
        m_input->poll();
		if (glfwGetKey(m_glwindow, GLFW_KEY_F)){
			m_lights[0].setPosition(*m_camera.getPosition());
		}
		m_camera.updateViewMatrix();
		frame_counter++;
		for (unsigned i = 0; i < m_lights.size(); i++){
			if (m_lights[i].getType() == DIRECTIONAL){
				directionalGLPass(&m_lights[i]);
			}
			else if (m_lights[i].getType() == POINT){
				pointGLPass(&m_lights[i]);
			}
		}
        glfwSwapBuffers(m_glwindow);

#if 0
		avg_rate += (float)glfwGetTime();
		avg_rate *= 0.5f;
        glfwSetTime(0.0);
		frame_counter++;
		if (frame_counter >= 60){
			frame_counter = 0;
			printf("framerate: %f\n", 1.0f / avg_rate);
			glm::vec3* pos = m_camera.getPosition();
			printf("position: %f, %f, %f\n", pos->x, pos->y, pos->z);
		}
#endif
    }
}
