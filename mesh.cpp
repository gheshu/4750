#include "mesh.h"
#include "myglheaders.h"
#include "objimporter.h"
#include "debugmacro.h"

Mesh::Mesh(const std::string& filename, unsigned mat) : material(mat){
	num_vertices = 0;
	MeshData data;
	objload(filename, data, true, true);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(hlm::vec3) * 1));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(hlm::vec3) * 2));
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	num_vertices = data.vertices.size();
	MYGLERRORMACRO
}

Mesh::~Mesh(){
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	MYGLERRORMACRO
}

void Mesh::draw(){
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	glBindVertexArray(0);
	MYGLERRORMACRO
}
