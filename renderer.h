#ifndef RENDERER_H
#define RENDERER_H

#include "myglheaders.h"
#include "camera.h"
#include "glsl_program.h"
#include "texture.h"
#include "mesh.h"
#include "light.h"

#include <string>

class Input;
class Window;

class Renderer
{
private:
	Camera m_camera;
	GLSLProgram m_program, shadow_program, omni_shadow_program;
	std::vector<Mesh> m_meshes;
	std::vector<Light> m_lights;
	std::vector<Texture> m_textures;
	Input* m_input;
	Window* m_window;
	GLFWwindow* m_glwindow;

	GLuint SHADOW_WIDTH, SHADOW_HEIGHT, depthMapFBO, depthCubeFBO, depthMap, depthCubemap, m_width, m_height;

	void directionalGLPass(Light* light);
	void pointGLPass(Light* light);
	void depthPassInit();
	void depthPass();
public:
    void init(const int width, const int height, const int msaa);
	void destroy();
    void draw();

};
#endif
