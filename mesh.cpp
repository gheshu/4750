#include "mesh.h"
#include "myglheaders.h"
#include "objimporter.h"

MeshData::MeshData(const std::string& filename){
	num_indices = 0;
	if(!objload(filename, &*this)) return;
	if (vertices.empty() || indices.empty()) return;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * vertices.size(), &vertices.first[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	num_indices = indices.size();
	MYGLERRORMACRO
}

MeshData::~MeshData(){
	glDeleteBuffers(1, &ibuf);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	vertices.clear();
	indices.clear();
	MYGLERRORMACRO
}

void MeshData::draw(){
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	MYGLERRORMACRO
}
