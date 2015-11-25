#include "mesh.h"
#include "myglheaders.h"
#include "objimporter.h"
#include "debugmacro.h"

Mesh::Mesh(const std::string& filename){
	num_indices = 0;
	MeshData data;
	objload(filename, data, true, true);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibuf);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data.vertices[0]), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data.vertices[0]), 
		(void*)(sizeof(data.vertices[0].position)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(data.vertices[0]), 
		(void*)(sizeof(data.vertices[0].position) + sizeof(data.vertices[0].normal)));
	glBufferData(GL_ARRAY_BUFFER, sizeof(data.vertices[0]) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data.indices[0]) * data.indices.size(), &data.indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	num_indices = data.indices.size();
	MYGLERRORMACRO
}

Mesh::~Mesh(){
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibuf);
	glDeleteVertexArrays(1, &vao);
	MYGLERRORMACRO
}

void Mesh::draw(){
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	MYGLERRORMACRO
}
