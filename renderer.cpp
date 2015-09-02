
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"

using namespace std;
using namespace hlm;

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
	
	if(!m_prog.build("shaders/main.vert", "shaders/main.frag")){
		exit(1);
	}
	fbs[0].init();
	fbs[1].init();
	
	screenQuadInit(m_vao, fb_ids[0], fb_ids[1]);
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

void Renderer::DDAPass(mat4& proj, VertexBuffer& verts, Image& img){
	for(unsigned i = 0; i < verts.size(); i += 3){
		vec3 face[3];
		face[0] = vec3(proj * vec4(verts[i]));
		face[1] = vec3(proj * vec4(verts[i + 1]));
		face[2] = vec3(proj * vec4(verts[i + 2]));
			
		for(int t = 0; t < 3; t++){
			vec3& v1 = face[t%3];
			vec3& v2 = face[(t + 1)%3];
			float slope = (v2.y - v1.y) / (v2.x - v1.x);
			if(abs(slope) > 1.0f){
				slope = 1.0f / slope;
				int x = (int)round(v1.x);
				int k = 0;
				for(int y = (int)round(v1.y); y <= (int)round(v2.y); y++){
					img.setPixel(x, y, 255, 0, 0, 0);
					x = (int)round(v1.x + (float)k * slope);
					k++;
				}
			} 
			else {
				int y = (int)round(v1.y);
				int k = 0;
				for(int x = (int)round(v1.x); x <= (int)round(v2.x); x++){
					img.setPixel(x, y, 255, 0, 0, 0);
					y = (int)round(v1.y + (float)k * slope);
					k++;
				}
			}
		}
	}
}

void Renderer::draw() {
	float avg_rate = 0.0f;
	unsigned frame_counter = 0;
	bool front_buffer = true;
	unsigned i = 0;
	mat4 proj;
	hlm::orthoToPixels(proj, m_width, m_height, -1, 1, -1, 1, 0.1f, 100.0f, 90.0f);
    while (!glfwWindowShouldClose(m_glwindow)) {
		m_input->poll();
		
		DDAPass(m_camera, verts, fbs[i]);
		bresenhamPass(m_camera, verts, fbs[i]);
		glPass(m_prog, fbs[i], m_vao, fb_ids[i]);
		
        glfwSwapBuffers(m_glwindow);
		i = (i + 1) % 2;
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
