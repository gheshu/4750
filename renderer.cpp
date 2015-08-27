
#include "renderer.h"
#include <iostream>
#include "debugmacro.h"
#include "window.h"
#include "input.h"
#include "hlm/hlm.h"

#include <algorithm>

using namespace std;

void Renderer::destroy() {
	fb1.unload();
	fb0.unload();
    delete m_window;
	m_window = nullptr;
	delete m_input;
	m_input = nullptr;
}

void Renderer::init(const int width, const int height, const int msaa) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "CSC4750");
	m_glwindow = m_window->getWindow();
	m_input = new Input(m_glwindow);
	m_camera.init(90.0f, (float)m_width / (float)m_height, 0.1f, 10.0f, hlm::vec3(-1.0f, 1.0f, -1.0f));
	
	if(!m_prog.build("shaders/main.vert", "shaders/main.frag")){
		exit(1);
	}
	
	fb0.load("images/test.png");
	fb1.init("images/empty.png");
	screenQuadInit(m_vao, fb0_id, fb1_id);
	MYGLERRORMACRO
}

void Renderer::screenQuadInit(GLuint& vao, GLuint& id0, GLuint& id1){
    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    static const GLfloat coords[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
        -1.0f, -1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords[0]) * 12, coords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
	
	glGenTextures(1, &id0);
	glGenTextures(1, &id1);
	glBindTexture(GL_TEXTURE_2D, id0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, id1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	MYGLERRORMACRO
}

void Renderer::glPass(GLSLProgram& prog, Image& img, GLuint& vao, GLuint& fb_id){
	prog.bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fb_id);
	prog.setUniformInt("image", 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, img.data);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	MYGLERRORMACRO
}

void Renderer::bresenhamPass(Camera& cam, VertexBuffer& verts, Image& img){
	
}

void Renderer::draw() {
	float avg_rate = 0.0f;
	unsigned frame_counter = 0;
	bool front_buffer = true;
    while (!glfwWindowShouldClose(m_glwindow)) {
		m_input->poll();
		m_camera.updateViewMatrix();
		
		if(front_buffer){
			bresenhamPass(m_camera, verts, fb0);
			glPass(m_prog, fb0, m_vao, fb0_id);
			front_buffer = false;
		} else {
			bresenhamPass(m_camera, verts, fb1);
			glPass(m_prog, fb0, m_vao, fb1_id);
			front_buffer = true;
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
		}
#endif
    }
}
