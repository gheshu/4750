#include "mesh.h"
#include "myglheaders.h"

Mesh::Mesh(){
	num_indices = 0;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibuf);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(hlm::vec3) * 1));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(hlm::vec3) * 2));
	glBindVertexArray(0);
}

Mesh::~Mesh(){
	glDeleteBuffers(1, &ibuf);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	MYGLERRORMACRO
}

void Mesh::uploadData(VertexBuffer& verts, IndexBuffer& indices){
	if (verts.empty() || indices.empty()){
		return;
	}
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	num_indices = indices.size();
	MYGLERRORMACRO
}

void Mesh::draw(){
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	MYGLERRORMACRO
}
