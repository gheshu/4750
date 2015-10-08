
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"
#include "objimporter.h"
#include "entitygraph.h"

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
	res_man.init(1);
	res_man.load("assets/sphere.obj", "sphere");
}

void Renderer::destroy(){
	res_man.destroy();
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

void Renderer::glPass(const Image& img, const GLuint vao, const GLuint fb_id){
	glBindTexture(GL_TEXTURE_2D, fb_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, img.data);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	MYGLERRORMACRO
}

void Renderer::DDAPass(const mat4& proj, Mesh* mesh, Image& img){
	const Pixel color(0xFF, 0xFF, 0xFF, 0xFF);
	for(unsigned i = 0; i < mesh->indices.size() - 2; i += 3){
		vec4 face[3];
		face[0] = proj * mesh->vertices[mesh->indices[i]].position;
		face[1] = proj * mesh->vertices[mesh->indices[i+1]].position;
		face[2] = proj * mesh->vertices[mesh->indices[i+2]].position;
		for(unsigned t = 0; t < 3; t++){
			// divide into correct perspective
			face[t] = face[t] / face[t].w;
		}
		
		for(int t = 0; t < 3; t++){
			const vec4& v1 = face[t%3];
			const vec4& v2 = face[(t + 1)%3];
			
			const bool steep = abs(v2.y - v1.y) > abs(v2.x - v1.x);
			float x0, x1, y0, y1;
			if(steep){
				x0 = v1.y;
				x1 = v2.y;
				y0 = v1.x;
				y1 = v2.x;
			} 
			else{
				x0 = v1.x;
				x1 = v2.x;
				y0 = v1.y;
				y1 = v2.y;
			} 
			if(x0 > x1){
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			const float dx = x1 - x0;
			const float dy = y1 - y0;
			float slope;
			if(dx == 0.0f){
				slope = 9999999.0f;
			}
			else {
				slope = dy / dx;
			}
			if(steep){
				int k = 0;
				for(int x = (int)(x0); x < (int)(x1); x++){
					int y = (int)(y0 + k * slope);
					img.setPixel(y, x, color);
					k++;
				}
			}
			else {
				int k = 0;
				for(int x = (int)(x0); x < (int)(x1); x++){
					int y = (int)(y0 + k * slope);
					img.setPixel(x, y, color);
					k++;
				}
			}
		}
	}
}

void Renderer::draw(const BoshartParam& param) {
	//-----scenegraph code----------------------------
	EntityGraph graph;
	graph.init(4);
	Transform t;
	t.add(T, param.t);
	t.add(R, param.r, length(param.r));
	t.add(S, param.s);
	graph.insert("sphere", "root", "sphere", t);
	graph.update();
	std::vector<MeshTransform>* instance_xforms = graph.getTransforms();
	//----end scenegraph code----------------------------
	printf("W:\n");
	mat4 W = Wmatrix((float)m_width, (float)m_height);
	print(W);
	printf("N:\n");
	mat4 N = Nmatrix(param.near, param.far);
	print(N);
	printf("A:\n");
	mat4 A = Amatrix((float)m_height / (float)m_width, param.fov);
	print(A);
	printf("C:\n");
	mat4 C = lookAt(param.eye, param.at, param.up);
	print(C);
	printf("WNAC:\n");
	const mat4 WNAC = W * N * A * C;
	print(WNAC);
	printf("\n");
	const Pixel black(0, 0, 0, 0xFF);
	m_prog.bind();
	
	//------------draw loop-----------------------------
	unsigned frame_i = 0;
	glfwSetTime(0.0);
	bool insert = false;
    while (!glfwWindowShouldClose(m_glwindow)) {
		
		m_input->poll();
		fb.clear(black);
	
		// draw each mesh instance
		for(int i = 0; i < instance_xforms->size(); i++){
			MeshTransform& mt = instance_xforms->at(i);
			mat4 WNACI = WNAC * mt.mat;
			Mesh* mesh = res_man.get(mt.mesh_id);
			if(mesh){
				DDAPass(WNACI, mesh, fb);
			}
		}

		// send framebuffer to opengl
		glPass(fb, m_vao, fb_id);
        glfwSwapBuffers(m_glwindow);
		frame_i++;
		
		if(frame_i >= 60){
			frame_i = 0;
			cout << "fps: " << (1.0f / (glfwGetTime() / 60.0f)) << endl;
			glfwSetTime(0.0);
			
			// insert or remove something for memory tests
			if(insert){
				insert = false;
			}
			else{
				insert = true;
			}
			
		}
    }
	//---------end draw loop--------------------------------
	instance_xforms = nullptr;
	graph.destroy();
}
