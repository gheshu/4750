
#include "renderer.h"
#include <iostream>
#include "debugmacro.h"
#include "window.h"

#include <algorithm>

using namespace std;

void Renderer::destroy() {
    delete m_window;
	m_window = nullptr;
}

void Renderer::init(const int width, const int height, const int msaa) {
	m_width = width; m_height = height;
	m_window = new Window(width, height, 3, 3, msaa, "CSC4750");
	m_glwindow = m_window->getWindow();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	MYGLERRORMACRO
}

void Renderer::bresenhamPass(){
	
}

void Renderer::draw() {
	float avg_rate = 0.0f;
	unsigned frame_counter = 0;
    while (!glfwWindowShouldClose(m_glwindow)) {
		bresenhamPass();
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
