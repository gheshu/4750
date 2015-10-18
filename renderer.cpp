
#include "renderer.h"
#include <iostream>
#include <algorithm>
#include "debugmacro.h"
#include "objimporter.h"
#include "entitygraph.h"

#ifdef OMP_PARALLEL
	#include "omp.h"
#endif

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
	
	framebuffer.init(m_width, m_height);
	depthbuffer.init(m_width, m_height);
	
	screenQuadInit();
	res_man.init(1);
	res_man.loadNoIndices("assets/sphere.obj", "sphere");
}

void Renderer::destroy(){
	res_man.destroy();
	depthbuffer.destroy();
	framebuffer.destroy();
    delete m_window;
	m_window = nullptr;
	delete m_input;
	m_input = nullptr;
}

void Renderer::screenQuadInit(){
    GLuint vbo;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(m_vao);
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
	
	glGenTextures(1, &fb_id);
	glBindTexture(GL_TEXTURE_2D, fb_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	MYGLERRORMACRO
}

void Renderer::glPass(){
	glBindTexture(GL_TEXTURE_2D, fb_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, framebuffer.width, framebuffer.height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, framebuffer.data);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	MYGLERRORMACRO
}

void Renderer::fillPass(const mat4& proj, Mesh* mesh, const unsigned i){
	vec4 face[3];
	face[0] = proj * mesh->at(i).position;
	face[1] = proj * mesh->at(i + 1).position;
	face[2] = proj * mesh->at(i + 2).position;
	// bounds checks and early exits
	unsigned badz = 0;
	for(unsigned t = 0; t < 3; t++){
		// divide into correct perspective
		face[t] = face[t] / face[t].w;
		if(face[t].z < -1.0f || face[t].z > 1.0f){
			badz++;
		}
	}
	if(badz >= 3){
		//badz == 3 means all vertices of face are clipped leaving nothing to draw.
		return;
	}
	{
		// do back face culling
		const vec3 e1(face[1] - face[0]);
		const vec3 e2(face[2] - face[0]);
		const vec3 fnormal = cross(e1, e2);
		if(fnormal.z <= 0.0f){
			// z component of normal must not face away (musn't be negative)
			// negative z is 'away' in camera space.
			return;
		}
	}
	// clamp the vertices to the screen.
	for(unsigned t = 0; t < 3; t++){
		face[t].x = clamp(0.0f, m_width - 1.0f, face[t].x);
		face[t].y = clamp(0.0f, m_height - 1.0f, face[t].y);
	}
	// retrieve the vertex colors.
	const vec3& c0 = mesh->at(i).color;
	const vec3 ce1 = mesh->at(i+1).color - c0;
	const vec3 ce2 = mesh->at(i+2).color - c0;
	// determine edges
	const vec3 e1(face[1] - face[0]);
	const vec3 e2(face[2] - face[0]);
	// calculate deltas
	const float da = 1.0f / max(1.0f, length(e1));
	const float db = 1.0f / max(1.0f, length(e2));
	// draw loop
	const vec3 v0(face[0]);
	for(float b = 0.0f; b <= 1.0f; b += db){
		for(float a = 0.0f; a <= 1.0f; a += da){
			if(a + b > 1.0f){
				continue;
			}
			const vec3 point(v0 + a * e1 + b * e2);
			if(depthbuffer.top(point)){
				vec3 color;
				if(vertex_shading){
					color = normalize(c0 + a * ce1 + b * ce2);
				}
				else{
					color = m_param.mat;
				}
				#pragma omp critical
				{
					framebuffer.setPixel(point, color);
					depthbuffer.set(point);
				}
			}
		}
	}
}

void Renderer::draw(const BoshartParam& param) {
	m_param = param;
	vertex_shading = true;
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
	
	const mat4 PW = Wmatrix((float)m_width, (float)m_height) 
		* GLperspective(param.fov, (double)m_width / (double)m_height, param.near, param.far);
	m_prog.bind();
	
	//------------draw loop-----------------------------
	
	glfwSetTime(0.0);
	unsigned frame_i = 0;
	Camera cam;
	cam.init(param.eye, param.at, param.up);
	glfwSetTime(0.0);
	
    while (!glfwWindowShouldClose(m_glwindow)) {
		// update frame time
		double dt = glfwGetTime();
		glfwSetTime(0.0);
		frame_i++;
		if(frame_i % 60 == 0){
			printf("FPS: %f\n", 1.0 / dt);
		}
		
		// update camera and poll glfw events
		m_input->poll(dt, cam);
		if(glfwGetKey(m_glwindow, GLFW_KEY_R)){
			cam.init(param.eye, param.at, param.up);
		}
		if(glfwGetKey(m_glwindow, GLFW_KEY_C)){
			vertex_shading = false;
		}
		else if(glfwGetKey(m_glwindow, GLFW_KEY_V)){
			vertex_shading = true;
		}
		const mat4 VPW = PW * cam.getViewMatrix();
		
		// clear frame
		framebuffer.clear();
		depthbuffer.clear();
		
		// draw each mesh instance
		for(unsigned i = 0; i < instance_xforms->size(); i++){
			MeshTransform& mt = instance_xforms->at(i);
			mat4 MVPW = VPW * mt.mat;
			Mesh* mesh = res_man.get(mt.mesh_id);
			if(mesh){
				#pragma omp parallel for schedule(dynamic, 4)
				for(unsigned k = 0; k < mesh->num_verts() / 3; k++){
					fillPass(MVPW, mesh, k * 3);
				}
			}
		}

		// send framebuffer to opengl
		glPass();
		glfwSwapBuffers(m_glwindow);
    }
	//---------end draw loop--------------------------------
	instance_xforms = nullptr;
	graph.destroy();
}
