#pragma once

#include "Common.h"

class ShaderProgram {
public:
	ShaderProgram();

	void loadShader(const std::string& shaderPath);
	void linkProgram();
	void useProgram();

private:
	void checkShaderCompilation(GLuint shader, const std::string& typeName);
	void checkProgramLinkage();

	GLuint _program;
	std::vector<GLuint> _shaders;
};