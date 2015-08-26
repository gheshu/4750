#include "glsl_program.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#include "debugmacro.h"
// ----------------------------------------------------------------------------

GLSLProgram::GLSLProgram() : program_(0)
{

}

// ----------------------------------------------------------------------------

GLSLProgram::~GLSLProgram()
{
	if (program_ > 0)
	{
		glDeleteProgram(program_);
	}
}

// ----------------------------------------------------------------------------

bool GLSLProgram::build(const std::string& vert, const std::string& frag){
	if (!this->initialise()){
		printf("glsl program initialisation problem\n");
		return false;
	}
	else if (!this->compileShader(ShaderType_Vertex, vert)){
		printf("vertex compilation problem\n");
		return false;
	}
	else if (!this->compileShader(ShaderType_Fragment, frag)){
		printf("fragment compilation problem\n");
		return false;
	}
	else if (!this->link()){
		printf("glsl program link problem\n");
		return false;
	}
	return true;
}

bool GLSLProgram::build(const std::string& vert, const std::string& geom, const std::string& frag){
	if (!this->initialise()){
		printf("glsl program initialisation problem\n");
		return false;
	}
	else if (!this->compileShader(ShaderType_Vertex, vert)){
		printf("vertex compilation problem\n");
		return false;
	}
	else if (!this->compileShader(ShaderType_Geometry, geom)){
		printf("geometry compilation problem\n");
		return false;
	}
	else if (!this->compileShader(ShaderType_Fragment, frag)){
		printf("fragment compilation problem\n");
		return false;
	}
	else if (!this->link()){
		printf("glsl program link problem\n");
		return false;
	}
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::initialise()
{
	program_ = glCreateProgram();
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

void GLSLProgram::bind(){
	glUseProgram(program_);
	MYGLERRORMACRO
}

void GLSLProgram::unbind(){
	glUseProgram(0);
	MYGLERRORMACRO
}

// ----------------------------------------------------------------------------

void GLSLProgram::printShaderInfo(GLuint shader) const
{
	int infoLogLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> shaderErrorMessage(std::max(infoLogLength, int(1)));
	glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &shaderErrorMessage[0]);
}

// ----------------------------------------------------------------------------

void GLSLProgram::printProgramInfo(GLuint program) const
{
	int infoLogLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(infoLogLength, int(1)));
	glGetProgramInfoLog(program, infoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
}

// ----------------------------------------------------------------------------

void GLSLProgram::prependLine(const std::string& line)
{
	header_ += line;
	header_ += "\n";
}

// ----------------------------------------------------------------------------

bool loadFile(const std::string& path, std::string& data)
{
	std::ifstream file(path.c_str());
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	data = fileData.str();

	return true; 
}

// ----------------------------------------------------------------------------

bool GLSLProgram::compileShader(GLSLShaderTypes type, const std::string& filePath)
{
	std::string data;
	if (!loadFile(filePath.c_str(), data))
	{
		printf("Error: could not load file %s\n", filePath.c_str());
		return false;
	}

	const GLchar* inputCode[] = { header_.c_str(), data.c_str() };

	GLenum glShaderType;
	switch (type){
	case ShaderType_Vertex:
		glShaderType = GL_VERTEX_SHADER;
		break;
	case ShaderType_Geometry:
		glShaderType = GL_GEOMETRY_SHADER;
		break;
	case ShaderType_Fragment:
		glShaderType = GL_FRAGMENT_SHADER;
		break;
	}

	const GLuint shader = glCreateShader(glShaderType);
	glShaderSource(shader, 2, inputCode, NULL);
	glCompileShader(shader);

	GLint status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		MYGLERRORMACRO
		printShaderInfo(shader);
		return false;
	}

	glAttachShader(program_, shader);
	shaders_.push_back(shader);

	MYGLERRORMACRO

	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::link()
{
	if (shaders_.empty())
	{
		return true;
	}

	glLinkProgram(program_);

	GLint status = GL_FALSE;
	glGetProgramiv(program_, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		MYGLERRORMACRO
		printProgramInfo(program_);
		return false;
	}

	for (size_t i = 0; i < shaders_.size(); i++)
	{
		glDetachShader(program_, shaders_[i]);
		glDeleteShader(shaders_[i]);
	}

	shaders_.clear();

	MYGLERRORMACRO

	return true;
}

// ----------------------------------------------------------------------------

GLuint GLSLProgram::getId() const
{
	return program_;
}

// ----------------------------------------------------------------------------

const GLint GLSLProgram::getUniformLocation(const std::string& name){
	const auto iter = uniformLocations_.find(name);	
	if (iter == uniformLocations_.end()){
		const GLint location = glGetUniformLocation(program_, name.c_str());
		MYGLERRORMACRO
		uniformLocations_[name] = location;
		return location;
	}
	return iter->second;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::getSubroutineIndex(const std::string& name, GLuint& uniform)
{
	// TODO hardcoded to fragment shaders
	uniform = glGetSubroutineIndex(program_, GL_FRAGMENT_SHADER, name.c_str());
	MYGLERRORMACRO
	return uniform != GL_INVALID_INDEX;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniform(const std::string& name, const glm::mat4& uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniform(const std::string& name, const glm::mat3& uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniform(const std::string& name, const glm::vec4& uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform4fv(location, 1, glm::value_ptr(uniform));
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniform(const std::string& name, const glm::vec3& uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform3fv(location, 1, glm::value_ptr(uniform));
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniformFloat(const std::string& name, const float uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform1f(location, uniform);
	MYGLERRORMACRO
	return true;
}

// ----------------------------------------------------------------------------

bool GLSLProgram::setUniformInt(const std::string& name, const GLuint uniform)
{
	const GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform1i(location, uniform);
	MYGLERRORMACRO
	return true;
}

