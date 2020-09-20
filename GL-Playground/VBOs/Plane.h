#pragma once

#include "Common.h"

class Plane {
public:
	Plane(const glm::vec3& center, const float width, const float height);
	Plane(const glm::vec3& min, const glm::vec3& max);

	// Maybe future constructors
	// Plane(const glm::vec3& lowerLeft, const glm::vec3& upperLeft, const glm::vec3& lowerRight, const glm::vec3& upperRight);
	// some kind of subdivision parameter (might be useful for terrain generation)

	void render();

private:
	GLuint _vao;

	void init();
	std::vector<glm::vec3> _vertices, _normals;
	std::vector<glm::vec2> _textureCoords;
	std::vector<unsigned int> _indices;
};