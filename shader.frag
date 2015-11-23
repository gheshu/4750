#version 330 core

smooth in vec3 worldPos_f;
smooth in vec3 normal_f;
smooth in vec2 uv_f;

uniform sampler2D diffuse_tex;
uniform sampler2D normal_tex;
uniform vec2 uv_scale;
uniform vec2 uv_offset;

uniform float spec_exp;
uniform float spec_str;
uniform vec3 ambient;

#define MAX_LIGHTS 10
uniform int numLights;
uniform struct Light{
	vec3 position;
	vec3 color;
	vec3 falloff;
} lights[MAX_LIGHTS];

uniform vec3 eye;

out vec4 out_color;

void main(){
	vec2 uv = uv_f * uv_scale + uv_offset;
	vec3 tex_normal = normalize(texture(normal_tex, uv).rgb * 2.0 - 1.0);
	vec3 model_normal = normalize(normal_f);
	vec3 N = normalize(vec3(model_normal.x + tex_normal.x, model_normal.y + tex_normal.y, 
		model_normal.z * tex_normal.z));
	vec3 C = texture(diffuse_tex, uv).rgb;
	vec3 V = normalize(eye - worldPos_f);
	
	vec3 diffuse = vec3(0.0, 0.0, 0.0);
	vec3 specular = vec3(0.0, 0.0, 0.0);
	
	for(int i = 0; i < numLights; i++){
		vec3 L = normalize(lights[i].position - worldPos_f);
		float d2 = dot(L, L);
		float d = sqrt(d2);
		float falloff = lights[i].falloff.x + lights[i].falloff.y * d + lights[i].falloff.z * d2;
		diffuse += (max(0.0, dot(N, L)) * C * lights[i].color) / falloff;
		vec3 H = normalize(L + V);
		float specAngle = max(dot(N, H), 0.0);
		specular += (spec_str * pow(specAngle, 4.0*spec_exp) * lights[i].color) / falloff;
	}
	
	out_color = vec4(ambient + diffuse + specular, 1.0);
}