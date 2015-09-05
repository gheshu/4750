#ifndef		HAS_GLSL_PROGRAM_H_BEEN_INCLUDED
#define		HAS_GLSL_PROGRAM_H_BEEN_INCLUDED

#include "myglheaders.h"
#include <vector>
#include <unordered_map>
#include "hlm.h"

enum GLSLShaderTypes
{
	ShaderType_Vertex,
	ShaderType_Geometry,
	ShaderType_Fragment
};

class GLSLProgram
{
public:

	GLSLProgram();
	virtual ~GLSLProgram();

	virtual bool initialise();
	void prependLine(const std::string& line);

	bool compileShader(GLSLShaderTypes type, const std::string& filePath);
	bool link();
	bool build(const std::string& vert, const std::string& frag);
	bool build(const std::string& vert, const std::string& geom, const std::string& frag);

	void bind();
	void unbind();

	GLuint getId() const;
	bool getUniform(const std::string& name, hlm::mat4& uniform);
	bool getSubroutineIndex(const std::string& name, GLuint& uniform);

	bool setUniform(const std::string& name, hlm::mat4& uniform);
	bool setUniform(const std::string& name, hlm::mat3& uniform);
	bool setUniform(const std::string& name, hlm::vec4& uniform);
	bool setUniform(const std::string& name, hlm::vec3& uniform);

	// NB: overloading deliberately avoided here to prevent problems with literals
	// being converted, e.g. with an integer setUniform func setUniform("bob", 1.f)
	// will call the variant, which can be very confusing (although it does generate a warning)
	bool setUniformFloat(const std::string& name, const float uniform);
	bool setUniformInt(const std::string& name, const GLuint uniform);

private:

	void printShaderInfo(GLuint shader) const;
	void printProgramInfo(GLuint program) const;

	GLuint					program_;
	std::vector<GLuint>		shaders_;
	std::string				header_;

	// Hash the locations of the uniforms to prevent glGet calls during frames
	typedef std::unordered_map<std::string, GLint> UniformLocations;
	UniformLocations		uniformLocations_;

	const GLint getUniformLocation(const std::string& name);
};

#endif	//	HAS_GLSL_PROGRAM_H_BEEN_INCLUDED

