#include "..\include\ShaderProgram.h"

#include <map>
#include <fstream>

std::map<std::string, GLenum> ShaderTypes = { {"vert", GL_VERTEX_SHADER}, {"frag", GL_FRAGMENT_SHADER} };

ShaderProgram::ShaderProgram()
{
	_program = glCreateProgram();
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


	std::string shaderExt = "";
	size_t loc = shaderPath.find_last_of('.');
	if (loc != std::string::npos)
		shaderExt = shaderPath.substr(loc, std::string::npos);

	//GLuint shader;
	GLenum shaderType = ShaderTypes[shaderExt]; // use ShaderTypes find to get an iterator which can be invalid
	//shader = glCreateShader(()
}

void ShaderProgram::linkShaders()
{
}

void ShaderProgram::useProgram()
{
}

void ShaderProgram::checkShaderCompilation(GLuint shader)
{
}

void ShaderProgram::checkProgramLinkage(GLuint program)
{
}
