#version 330 core

in vec2 texcoord;

uniform sampler2D image;

int main(){
	gl_FragColor = texture2D(image, texcoord);
}