#pragma once

#include "Common.h"


class ShaderProgram {
public:
	ShaderProgram();

	void loadShader(const std::string& shaderPath);
	void linkProgram();
	void useProgram();

	void setUniform(const char* name, bool b);
	void setUniform(const char* name, int i);
	void setUniform(const char* name, GLuint ui);
	void setUniform(const char* name, float x);
	void setUniform(const char* name, float x, float y);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z, float w);
	void setUniform(const char* name, const glm::vec2& v);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat3& m);
	void setUniform(const char* name, const glm::mat4& m);


private:
	void checkShaderCompilation(GLuint shader, const std::string& typeName);
	void checkProgramLinkage();

	GLuint _program;
	std::vector<GLuint> _shaders;
};