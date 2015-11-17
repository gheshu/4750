
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
	res_man.init(2);
	res_man.loadNoIndices("assets/cube_texture.obj", "cube", false, false);
	res_man.loadNoIndices("assets/sphere.obj", "sphere", true, true);
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
	// move to view-space
	vec4 face[3];
	face[0] = data.mv * data.mesh->at(i).position;
	face[1] = data.mv * data.mesh->at(i + 1).position;
	face[2] = data.mv * data.mesh->at(i + 2).position;
	float da, db;
		// check screen-space culling
		vec4 scr[3]; unsigned badz = 0;
		for(int s = 0; s < 3; s++){
			scr[s] = face[s];
			scr[s].w = 1.0f;
			scr[s] = data.pw * face[s];
			scr[s] = scr[s] / scr[s].w;
			if(scr[s].z > 1.0f || scr[s].z < -1.0f){
				badz++;
			}
		}
	{
		if(badz >= 3){
			return;
		}
		const vec4 scre1(scr[1] - scr[0]);
		const vec4 scre2(scr[2] - scr[0]);
		const vec3 fnormal = cross(scre1, scre2);
		if(fnormal.z <= 0.0f){
			return;
		}
		// calculate deltas
		da = 1.0f / (length(scre1) * 1.5f);
		db = 1.0f / (length(scre2) * 1.5f);
	}

	const vec4 e1(face[1] - face[0]);
	const vec4 e2(face[2] - face[0]);
	vec3 normals[3];
	normals[0] = normalize(data.norm_mat * data.mesh->at(i).normal);
	normals[1] = normalize(data.norm_mat * data.mesh->at(i+1).normal);
	normals[2] = normalize(data.norm_mat * data.mesh->at(i+2).normal);
	vec3 ne1(normals[1] - normals[0]);
	vec3 ne2(normals[2] - normals[0]);
	const vec2& uv0 = data.mesh->at(i).uv;
	const vec2& uv1 = data.mesh->at(i+1).uv;
	const vec2& uv2 = data.mesh->at(i+2).uv;
	TexLerpTri tlt(uv0, uv1, uv2, vec3(scr[0].w, scr[1].w, scr[2].w));
	// draw loop
	for(float b = 0.0f; b <= 1.0f; b += db){
		for(float a = 0.0f; a <= 1.0f; a += da){
			if(a + b > 1.0f){
				continue;
			}
			vec4 point(face[0] + a * e1 + b * e2);
			const vec3 frag_pos(point);
			point.w = 1.0f;
			point = data.pw * point;
			point = point / point.w;
			if(depthbuffer.top(point)){
				vec2 uv = tlt.texLerp(a, b);
				vec3 mat = data.texture->texelW(uv);
				vec3 color;	//blinn-phong shading model
				vec3 normal = normalize(normals[0] + a * ne1 + b * ne2);
				if(data.normal){
					vec3 texNorm = normalize(data.normal->texelW(uv));
					normal = normalize(vec3(normal.x + texNorm.x, normal.y + texNorm.y, normal.z * texNorm.z));
				}
				const vec3 light = normalize(data.light_pos - frag_pos);
				float d2 = dot(light, light);
				const float diffuse = max(0.0f, dot(light, normal));
				const vec3 H = normalize(light + vec3(0.0f, 0.0f, 1.0f));
				const float specular = pow( max(0.0f, dot(normal, H)), data.spec_power*4.0f);
				color = data.ambient + (mat * diffuse + specular) / (data.lin_atten + d2);
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
	Image ttu;
	ttu.loadFile("assets/TTU.png");
	Image moon;
	moon.loadFile("assets/MoonMap.png");
	Image normal;
	normal.loadFile("assets/MoonNormal.png");
	DrawData drawdata;
	drawdata.ambient = param.ambient;
	drawdata.mat = param.mat;
	drawdata.lin_atten = param.lin_atten;
	drawdata.spec_power = param.spec_power;
	drawdata.normal = nullptr;
	drawdata.texture = &ttu;
	
	//-----scenegraph code----------------------------
	
	EntityGraph graph;
	graph.init(4);
	Transform t;
	t.add(T, param.t);
	t.add(R, param.r);
	t.add(S, param.s);
	graph.insert("cube", "root", "cube", t);
	graph.update();
	std::vector<MeshTransform>* instance_xforms = graph.getTransforms();
	Transform t2;
	t2.add(R, vec3(0.0f, 180.0f, 0.0f));
	t2.add(S, vec3(2.0f));
	//----end scenegraph code----------------------------
	
	drawdata.pw = Wmatrix((float)m_width, (float)m_height) 
		* GLperspective(param.fov, (double)m_width / (double)m_height, param.near, param.far);
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
		if(glfwGetKey(m_glwindow, GLFW_KEY_1)){
			drawdata.texture = &moon;
			drawdata.normal = &normal;
			graph.insert("sphere", "root", "sphere", t2);
			graph.remove("cube");
			graph.update();
			instance_xforms = graph.getTransforms();
		}
		else if(glfwGetKey(m_glwindow, GLFW_KEY_2)){
			drawdata.texture = &ttu;
			drawdata.normal = nullptr;
			graph.insert("cube", "root", "cube", t);
			graph.remove("sphere");
			graph.update();
			instance_xforms = graph.getTransforms();
		}
		vec4 l_pos(param.light_pos);
		l_pos.w = 1.0f;
		l_pos = cam.getViewMatrix() * l_pos;
		drawdata.light_pos = vec3(l_pos);
		
		// clear frame
		framebuffer.clear();
		depthbuffer.clear();
		
		// draw each mesh instance
		for(unsigned i = 0; i < instance_xforms->size(); i++){
			MeshTransform& mt = instance_xforms->at(i);
			Mesh* mesh = res_man.get(mt.mesh_id);
			if(mesh){
				drawdata.mv = cam.getViewMatrix() * mt.mat;
				drawdata.norm_mat = transpose(inverse(mat3(drawdata.mv)));
				drawdata.mesh = mesh;
				#pragma omp parallel for schedule(dynamic, 8)
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
	ttu.unloadFile();
	moon.unloadFile();
	normal.unloadFile();
}
