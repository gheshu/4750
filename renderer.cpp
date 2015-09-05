
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"
#include "objimporter.h"

using namespace std;
using namespace hlm;

void Renderer::init(const int width, const int height, const int msaa) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "CSC4750");
	m_glwindow = m_window->getWindow();
	m_input = new Input(m_glwindow);
	
	if(!m_prog.build("shader.vert", "shader.frag")){
		exit(1);
	}
	fb.init(m_width, m_height);
	
	screenQuadInit(m_vao, fb_id);
}

void Renderer::destroy() {
	fb.destroy();
    delete m_window;
	m_window = nullptr;
	delete m_input;
	m_input = nullptr;
}

void Renderer::screenQuadInit(GLuint& vao, GLuint& id0){
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
	glBindTexture(GL_TEXTURE_2D, id0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	MYGLERRORMACRO
}

void Renderer::glPass(Image& img, GLuint& vao, GLuint fb_id){
	glBindTexture(GL_TEXTURE_2D, fb_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, img.data);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	MYGLERRORMACRO
}

void Renderer::DDAPass(mat4& proj, VertexBuffer& verts, Image& img){
	Pixel p(0, 0, 0, 0);
	for(unsigned i = 0; i < verts.size(); i += 3){
		vec4 face[3];
		face[0] = proj * verts[i];
		face[1] = proj * verts[i + 1];
		face[2] = proj * verts[i + 2];
		for(int t = 0; t < 3; t++){
			vec4& v1 = face[t%3];
			vec4& v2 = face[(t + 1)%3];
			float slope = (v2.y - v1.y) / (v2.x - v1.x);
			if(abs(slope) > 1.0f){
				slope = 1.0f / slope;
				int x = (int)round(v1.x);
				int k = 0;
				for(int y = (int)round(v1.y); y <= (int)round(v2.y); y++){
					img.setPixel(x, y, p);
					x = (int)round(v1.x + (float)k * slope);
					k++;
				}
			} 
			else {
				int y = (int)round(v1.y);
				int k = 0;
				for(int x = (int)round(v1.x); x <= (int)round(v2.x); x++){
					img.setPixel(x, y, p);
					y = (int)round(v1.y + (float)k * slope);
					k++;
				}
			}
		}
	}
}

void Renderer::bresenhamPass(mat4& proj, VertexBuffer& verts, Image& img){
	
}

void Renderer::draw() {
	float avg_rate = 0.0f;
	unsigned frame_counter = 0;
	mat4 proj;
	VertexBuffer verts;
	objload("test.obj", verts);
	Pixel w(0xFF, 0xFF, 0xFF, 0xFF);
	Pixel b(0, 0, 0, 0xFF);
	m_prog.bind();
    while (!glfwWindowShouldClose(m_glwindow)) {
		m_input->poll();
		fb.clear(b);
		DDAPass(proj, verts, fb);
		bresenhamPass(proj, verts, fb);
		for(int y = 0; y < 100; y++){
			for(int x = 0; x < 100; x++){
				fb.setPixel(x, y, w);
			}
		}
		glPass(fb, m_vao, fb_id);
        glfwSwapBuffers(m_glwindow);
    }
}
