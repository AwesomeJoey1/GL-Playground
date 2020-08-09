#pragma once

#include "Common.h"

class ShaderProgram {
public:
	ShaderProgram();

	void loadShader(const std::string& shaderPath);
	void linkShaders();
	void useProgram();

private:
	void checkShaderCompilation(GLuint shader);
	void checkProgramLinkage(GLuint program);

	GLuint _program;
	std::vector<GLuint> _shaders;
};