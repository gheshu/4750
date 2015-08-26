#ifndef		HAS_MESH_H_BEEN_INCLUDED
#define		HAS_MESH_H_BEEN_INCLUDED

#include <vector>

#include "myglheaders.h"
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// ----------------------------------------------------------------------------

struct MeshVertex
{
	MeshVertex(const glm::vec3& _xyz, const glm::vec3& _normal, const glm::vec2& _uv)
		: xyz(_xyz), normal(_normal), uv(_uv) { };

	glm::vec3 xyz, normal;
	glm::vec2 uv;
};

struct Transform{
	glm::quat orientation;
	glm::vec3 position, scale;
	Transform() : orientation(glm::quat()), position(glm::vec3(0.0f)), scale(glm::vec3(1.0f)){};
};

typedef std::vector<MeshVertex> VertexBuffer;
typedef std::vector<int> IndexBuffer;

// ----------------------------------------------------------------------------

class Mesh
{
private:
	glm::mat4		model_matrix;
	Transform		transform;
	GLuint			vertexArrayObj_, vertexBuffer_, indexBuffer_, numIndices_, matid;
public:
	void initialise(const int matid);
	void translate(const glm::vec3& v);
	void rotate(const float angle, const glm::vec3& vector);
	void scale(const glm::vec3& v);
	void setTransform(const Transform& trans);
	Transform* getTransform();
	void updateMat();
	void uploadData(VertexBuffer& verts, IndexBuffer& indices);
	void draw();
	void destroy();
	void loadFromFile(VertexBuffer& verts, IndexBuffer& indices, const std::string& file);
	void loadFromFile(const std::string& file);

	void setMatID(unsigned newmatid){ matid = newmatid; }
	const unsigned getMatID() const { return matid; }
	glm::mat4* getMatrix();

	const bool operator<(const Mesh& other) const {
		return matid < other.getMatID();
	}
};

// ----------------------------------------------------------------------------

#endif	//	HAS_MESH_H_BEEN_INCLUDED
