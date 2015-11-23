#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 MVP;
uniform mat4 model;
uniform mat3 normMat;

smooth out vec3 worldPos_f;
smooth out vec3 normal_f;
smooth out vec2 uv_f;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	worldPos_f = vec3(model * vec4(position, 1.0));
	normal_f = normMat * normal;
	uv_f = uv;
}