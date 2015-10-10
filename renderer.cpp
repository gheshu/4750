
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
	db.init(m_width, m_height);
	
	screenQuadInit();
	res_man.init(1);
	res_man.load("assets/sphere.obj", "sphere");
}

void Renderer::destroy(){
	res_man.destroy();
	db.destroy();
	fb.destroy();
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fb.width, fb.height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, fb.data);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	MYGLERRORMACRO
}

void Renderer::fillPass(const mat4& proj, Mesh* mesh){
	for(unsigned i = 0; i < mesh->indices.size() - 2; i += 3){
		vec4 face[3];
		face[0] = proj * mesh->vertices[mesh->indices[i]].position;
		face[1] = proj * mesh->vertices[mesh->indices[i+1]].position;
		face[2] = proj * mesh->vertices[mesh->indices[i+2]].position;
		// bounds checks and early exits
		bool badw = false;
		unsigned badz = 0;
		for(unsigned t = 0; t < 3; t++){
			// divide into correct perspective
			if(face[t].w == 0.0f){
				badw = true;
				break;
			}
			face[t] = face[t] / face[t].w;
			if(face[t].z < -1.0f || face[t].z > 1.0f){
				badz++;
			}
		}
		if(badw || badz >= 3){
			continue;
		}
		// check normal facing away
		vec3 e1(face[1] - face[0]);
		vec3 e2(face[2] - face[0]);
		vec3 fnormal = cross(e1, e2);
		if(fnormal.z <= 0.0f){
			continue;
		}
		fnormal = normalize(fnormal);
		// assign extents, minx maxx, miny, maxy
		vec4 extents(face[0].x, face[0].x, face[0].y, face[0].y);
		for(unsigned t = 1; t < 3; t++){
			extents.x = clamp(0.0f, m_width - 1.0f, std::min(extents.x, face[t].x));
			extents.y = clamp(0.0f, m_width - 1.0f, std::max(extents.y, face[t].x));
			extents.z = clamp(0.0f, m_height -1.0f, std::min(extents.z, face[t].y));
			extents.w = clamp(0.0f, m_height -1.0f, std::max(extents.w, face[t].y));
		}
		
		//compute beta => y
		
		//loop over y
			//loop over alpha => x
			
				//compute pixel lighting OR blend vertex lighting
			
				//draw to image if at top of zbuffer
		
	}
}

void Renderer::DDAPass(const mat4& proj, Mesh* mesh){
	const Pixel color(0xFF, 0xFF, 0xFF, 0xFF);
	for(unsigned i = 0; i < mesh->indices.size() - 2; i += 3){
		vec4 face[3];
		face[0] = proj * mesh->vertices[mesh->indices[i]].position;
		face[1] = proj * mesh->vertices[mesh->indices[i+1]].position;
		face[2] = proj * mesh->vertices[mesh->indices[i+2]].position;
		bool badw = false;
		for(unsigned t = 0; t < 3; t++){
			// divide into correct perspective
			if(face[t].w == 0.0f){
				badw = true;
				break;
			}
			face[t] = face[t] / face[t].w;
		}
		if(badw){
			continue;
		}
		for(int t = 0; t < 3; t++){
			if(face[t].z < -1.0 || face[t].z > 1.0){
				badw = true;
				break;
			}
			
		}
		if(badw){
			continue;
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
					fb.setPixel(y, x, color);
					k++;
				}
			}
			else {
				int k = 0;
				for(int x = (int)(x0); x < (int)(x1); x++){
					int y = (int)(y0 + k * slope);
					fb.setPixel(x, y, color);
					k++;
				}
			}
		}
	}
}

void Renderer::draw(const BoshartParam& param) {
	m_near = param.near; m_far = param.far;
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
	mat4 W = Wmatrix((float)m_width, (float)m_height);
	const mat4 PW = W * GLperspective(param.fov, (double)m_width / (double)m_height, param.near, param.far);
	const Pixel black(0, 0, 0, 0xFF);
	m_prog.bind();
	
	//------------draw loop-----------------------------
	glfwSetTime(0.0);
	bool insert = false;
	Camera cam;
	cam.init(param.eye, param.at, param.up);
	glfwSetTime(0.0);
    while (!glfwWindowShouldClose(m_glwindow)) {
		double dt = glfwGetTime();
		glfwSetTime(0.0);
		m_input->poll(dt, cam);
		fb.clear(black);
		db.clear();
	
		// draw each mesh instance
		for(int i = 0; i < instance_xforms->size(); i++){
			MeshTransform& mt = instance_xforms->at(i);
			mat4 MVPW = PW * cam.getViewMatrix() * mt.mat;
			Mesh* mesh = res_man.get(mt.mesh_id);
			if(mesh){
				DDAPass(MVPW, mesh);
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
