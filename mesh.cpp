#include "mesh.h"
#include <stdio.h>
#include "debugmacro.h"
#include "glm/gtc/matrix_transform.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

// ----------------------------------------------------------------------------

void Mesh::initialise(const int _matid){
	numIndices_ = 0;
	matid = _matid;
	model_matrix = glm::mat4(1.0f);

	glGenVertexArrays(1, &vertexArrayObj_);
	glGenBuffers(1, &vertexBuffer_);
	glGenBuffers(1, &indexBuffer_);

	glBindVertexArray(vertexArrayObj_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(glm::vec3) * 1));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(sizeof(glm::vec3) * 2));

	glBindVertexArray(0);

	MYGLERRORMACRO
}

// ----------------------------------------------------------------------------

void Mesh::translate(const glm::vec3& v){
	transform.position += v;
	model_matrix = glm::translate(model_matrix, v);
}

void Mesh::rotate(const float angle, const glm::vec3& vector){
	transform.orientation = glm::rotate(transform.orientation, angle, vector);
	model_matrix = glm::rotate(model_matrix, angle, vector);
}

void Mesh::scale(const glm::vec3& v){
	transform.scale *= v;
	model_matrix = glm::scale(model_matrix, v);
}

Transform* Mesh::getTransform(){
	return &transform;
}

glm::mat4* Mesh::getMatrix() {
	return &model_matrix;
}

// ----------------------------------------------------------------------------

void Mesh::uploadData(VertexBuffer& verts, IndexBuffer& indices)
{
	if (verts.empty() || indices.empty())
	{
		return;
	}

	glBindVertexArray(vertexArrayObj_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	numIndices_ = (GLuint)indices.size();
	glBindVertexArray(0);
	MYGLERRORMACRO
}

// ----------------------------------------------------------------------------

void Mesh::destroy()
{
	glDeleteBuffers(1, &indexBuffer_);
	glDeleteBuffers(1, &vertexBuffer_);
	glDeleteVertexArrays(1, &vertexArrayObj_);

	MYGLERRORMACRO
}

// -----------------------------------------------------------------------------

void Mesh::draw(){
	glBindVertexArray(vertexArrayObj_);
	glDrawElements(GL_TRIANGLES, numIndices_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	MYGLERRORMACRO
}

// -----------------------------------------------------------------------------

glm::vec3 ass3glm3(const aiVector3D& rhs){
	return glm::vec3(rhs.x, rhs.y, rhs.z);
}

glm::vec2 ass3glm2(const aiVector3D& rhs){
	return glm::vec2(rhs.x, rhs.y);
}
glm::vec2 ass2glm2(const aiVector2D& rhs){
	return glm::vec2(rhs.x, rhs.y);
}

void Mesh::loadFromFile(VertexBuffer& verts, IndexBuffer& indices, const std::string& filename){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename.c_str(), 
		aiProcessPreset_TargetRealtime_Quality | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes);

	if (!scene){
		printf("cannot open scene from file %s\n", filename.c_str());
		return;
	}

	aiMesh* mesh = scene->mMeshes[0];
	for (GLuint i = 0; i < mesh->mNumVertices; i++){
		glm::vec3 pos = ass3glm3(mesh->mVertices[i]);
		glm::vec3 normal = ass3glm3(mesh->mNormals[i]);
		glm::vec2 uv = ass3glm2(mesh->mTextureCoords[0][i]);
		verts.push_back(MeshVertex(pos, normal, uv));
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++){
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++){
			indices.push_back(face.mIndices[j]);
		}
	}
	

	#if 0
		printf("number of vertices: %u\n", verts.size());
		printf("number of indices: %u\n", indices.size());
		for (unsigned i = 0; i < verts.size(); i++){
			printf("(%f, %f, %f), (%f, %f, %f), (%f, %f)\n", verts[i].xyz.x, verts[i].xyz.y, verts[i].xyz.z,
				verts[i].normal.x, verts[i].normal.y, verts[i].normal.z, verts[i].uv.x, verts[i].uv.y);
		}
		for (unsigned i = 0; i < indices.size(); i++){
			printf("%i, ", indices[i]);
			printf("\n");
		}
	#endif
}

void Mesh::loadFromFile(const std::string& file){
	VertexBuffer verts;
	IndexBuffer indices;
	this->loadFromFile(verts, indices, file);
	this->uploadData(verts, indices);
}
