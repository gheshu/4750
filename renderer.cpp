
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

void Renderer::fillPass(const DrawData& data, const unsigned i){
	vec4 face[3];
	face[0] = data.mvp * data.mesh->at(i).position;
	face[1] = data.mvp * data.mesh->at(i + 1).position;
	face[2] = data.mvp * data.mesh->at(i + 2).position;
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
	
	vec3 v[3];
	vec3 normals[3]; vec3 ne1, ne2;
	if(data.face_normals){
		for(unsigned s = 0; s < 3; s++){
			v[s] = vec3(face[s]);
		}
		normals[0] = normalize(cross(v[1] - v[0], v[2] - v[0]));
	}
	else {
		normals[0] = data.imvp * data.mesh->at(i).normal;
		normals[1] = data.imvp * data.mesh->at(i+1).normal;
		normals[2] = data.imvp * data.mesh->at(i+2).normal;
		ne1 = normals[1] - normals[0];
		ne2 = normals[2] - normals[0];
	}
	
	vec3 c[3]; vec3 ce1, ce2;
	if(data.vertex_shading){
		for(int s = 0; s < 3; s++){
			float d2 = dot(v[s], v[s]);
			const vec3 light = normalize(data.light_pos - v[s]);
			float diffuse; vec3 ref;
			if(data.face_normals){
				diffuse = max(0.0f, dot(light, normals[0]));
				ref = reflect(vec3(0.0f, 0.0f, -1.0f), normals[0]);
			}
			else {
				diffuse = max(0.0f, dot(light, normals[s]));
				ref = reflect(vec3(0.0f, 0.0f, -1.0f), normals[s]);
			}
			const float specular = pow( max(0.0f, dot(ref, light)), data.spec_power);
			c[s] = data.ambient + (data.mat * diffuse + specular) / (data.lin_atten + d2);
			c[s] = clamp(0.0f, 1.0f, c[s]);
		}
		ce1 = c[1] - c[0];
		ce2 = c[2] - c[0];
	}
	const vec4 scre1(data.w_matrix * face[1] - data.w_matrix * face[0]);
	const vec4 scre2(data.w_matrix * face[2] - data.w_matrix * face[0]);
	const vec4 e1 = face[1] - face[0];
	const vec4 e2 = face[2] - face[0];
	// calculate deltas
	const float da = 1.0f / (sqrt(scre1.x*scre1.x + scre1.y*scre1.y + scre1.z*scre1.z) * 1.5f);
	const float db = 1.0f / (sqrt(scre2.x*scre2.x + scre2.y*scre2.y + scre2.z*scre2.z) * 1.5f);
	// draw loop
	for(float b = 0.0f; b <= 1.0f; b += db){
		for(float a = 0.0f; a <= 1.0f; a += da){
			if(a + b > 1.0f){
				continue;
			}
			vec4 point(face[0] + a * e1 + b * e2);
			const vec3 frag_pos(point);
			point = data.w_matrix * point;
			if(depthbuffer.top(point)){
				vec3 color;
				if(data.vertex_shading){
					color = c[0] + a * ce1 + b * ce2;
				}
				else {
					const vec3 normal(normals[0] + a * ne1 + b * ne2);
					const vec3 frag_pos(point);
					float d2 = dot(frag_pos, frag_pos);
					const vec3 light = normalize(data.light_pos - frag_pos);
					const float diffuse = max(0.0f, dot(light, normal));
					const vec3 ref = reflect(vec3(0.0f, 0.0f, -1.0f), normal);
					const float specular = pow( max(0.0f, dot(ref, light)), data.spec_power);
					color = data.ambient + (data.mat * diffuse + specular) / (data.lin_atten + d2);
				}
				color = clamp(0.0f, 1.0f, color);
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
	DrawData drawdata;
	drawdata.ambient = param.ambient;
	drawdata.mat = param.mat;
	drawdata.lin_atten = param.lin_atten;
	drawdata.spec_power = param.spec_power;
	
	//-----scenegraph code----------------------------
	
	EntityGraph graph;
	graph.init(4);
	Transform t;
	t.add(T, param.t);
	t.add(R, param.r);
	t.add(S, param.s);
	graph.insert("sphere", "root", "sphere", t);
	graph.update();
	std::vector<MeshTransform>* instance_xforms = graph.getTransforms();
	
	//----end scenegraph code----------------------------
	
	drawdata.w_matrix = Wmatrix((float)m_width, (float)m_height);
	const mat4 P = GLperspective(param.fov, (double)m_width / (double)m_height, param.near, param.far);
	m_prog.bind();
	
	//------------draw loop-----------------------------
	
	glfwSetTime(0.0);
	unsigned frame_i = 0;
	Camera cam;
	cam.init(param.eye, param.at, param.up);
	glfwSetTime(0.0);
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
			cam.init(param.eye, param.at, param.up);
		}
		if(glfwGetKey(m_glwindow, GLFW_KEY_F)){
			drawdata.face_normals = !drawdata.face_normals;
		}
		if(glfwGetKey(m_glwindow, GLFW_KEY_V)){
			drawdata.vertex_shading = !drawdata.vertex_shading;
		}
		if(!drawdata.vertex_shading){
			drawdata.face_normals = false;
		}
		const mat4 VP = P * cam.getViewMatrix();
		
		// clear frame
		framebuffer.clear();
		depthbuffer.clear();
		
		// draw each mesh instance
		for(unsigned i = 0; i < instance_xforms->size(); i++){
			MeshTransform& mt = instance_xforms->at(i);
			Mesh* mesh = res_man.get(mt.mesh_id);
			if(mesh){
				drawdata.mvp = VP * mt.mat;
				drawdata.imvp = transpose(inverse(mat3(drawdata.mvp)));
				drawdata.mesh = mesh;
				drawdata.light_pos = drawdata.imvp * param.light_pos;
				#pragma omp parallel for schedule(dynamic, 4)
				for(unsigned k = 0; k < mesh->num_verts() / 3; k++){
					fillPass(drawdata, k * 3);
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
