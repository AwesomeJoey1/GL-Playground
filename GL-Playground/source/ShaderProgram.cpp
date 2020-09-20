#include "..\include\ShaderProgram.h"

#include <map>
#include <fstream>

std::map<std::string, GLenum> ShaderTypes = { {"vert", GL_VERTEX_SHADER}, {"frag", GL_FRAGMENT_SHADER} };

ShaderProgram::ShaderProgram()
{
	_program = glCreateProgram();
	if (!_program)
		std::cerr << "SHADER PROGRAM ERROR: Could not creat program\n";
}

void ShaderProgram::loadShader(const std::string& shaderPath)
{
	std::ifstream file;
	file.open(shaderPath, std::ios::in);

	if (!file)
	{
		std::cerr << "SHADER LOAD ERROR: Could not load shader from path: " << shaderPath << "\n";
		exit(EXIT_FAILURE);
	}

	std::string shaderCode = "";
	std::string line = "";
	while (!file.eof())
	{
		std::getline(file, line);
		shaderCode.append(line + "\n");
	}
	file.close();

	const char* shaderCodePtr = shaderCode.c_str();


	std::string shaderExt = "";
	size_t loc = shaderPath.find_last_of('.');
	if (loc != std::string::npos)
		shaderExt = shaderPath.substr(loc+1, std::string::npos);


	GLuint shader;
	GLenum shaderType = ShaderTypes[shaderExt]; // use ShaderTypes find to get an iterator which can be invalid
	if (!shaderType)
		std::cerr << "SHADER EXTENSION ERROR: Shader extension " << shaderExt << " is not valid.\n";
	
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCodePtr, NULL);

	glCompileShader(shader);
	checkShaderCompilation(shader, "VERTEX");
	_shaders.push_back(shader);
}

void ShaderProgram::linkProgram()
{
	for (auto s : _shaders)
	{
		glAttachShader(_program, s);
	}
	glLinkProgram(_program);
	checkProgramLinkage();

	for (auto s : _shaders)
	{
		glDetachShader(_program, s);
		glDeleteShader(s);
	}
}

void ShaderProgram::useProgram()
{
	glUseProgram(_program);
}

void ShaderProgram::setUniform(const char* name, bool b)
{
	GLuint bID = glGetUniformLocation(_program, name);
	glUniform1i(bID, b);
}

void ShaderProgram::setUniform(const char* name, int i)
{
	GLuint iID = glGetUniformLocation(_program, name);
	glUniform1i(iID, i);
}

void ShaderProgram::setUniform(const char* name, GLuint ui)
{
	GLuint uiID = glGetUniformLocation(_program, name);
	glUniform1ui(uiID, ui);
}

void ShaderProgram::setUniform(const char* name, float x)
{
	GLuint fID = glGetUniformLocation(_program, name);
	glUniform1f(fID, x);
}

void ShaderProgram::setUniform(const char* name, float x, float y)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform2f(vID, x, y);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform3f(vID, x, y, z);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z, float w)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform4f(vID, x, y, z, w);
}

void ShaderProgram::setUniform(const char* name, const glm::vec2& v)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform2f(vID, v.x, v.y);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& v)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform3f(vID, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& v)
{
	GLuint vID = glGetUniformLocation(_program, name);
	glUniform4f(vID, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const char* name, const glm::mat3& m)
{
	GLuint mID = glGetUniformLocation(_program, name);
	glUniformMatrix3fv(mID, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& m)
{
	GLuint mID = glGetUniformLocation(_program, name);
	glUniformMatrix4fv(mID, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::checkShaderCompilation(GLuint shader, const std::string &typeName)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << typeName << " SHADER COMPILE ERROR: " << infoLog << "\n";
	}
}

void ShaderProgram::checkProgramLinkage()
{
	int programSuccess;
	char programInfoLog[512];
	glGetProgramiv(_program , GL_LINK_STATUS, &programSuccess);

	if (!programSuccess) {
		glGetProgramInfoLog(_program, 512, NULL, programInfoLog);
		std::cerr << "SHADER PROGRAM LINK ERROR: " << programInfoLog << "\n";
	}
}
