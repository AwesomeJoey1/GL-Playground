#include "Plane.h"

// Axis aligned plane (xy plane)
Plane::Plane(const glm::vec3& center, const float width, const float height)
{
	float xInc = width / 2.0f;
	float yInc = height / 2.0f;
	_vertices.push_back(glm::vec3(center.x - xInc, center.y - yInc, center.z)); // lower left
	_vertices.push_back(glm::vec3(center.x - xInc, center.y + yInc, center.z)); // upper left
	_vertices.push_back(glm::vec3(center.x + xInc, center.y - yInc, center.z)); // lower right
	_vertices.push_back(glm::vec3(center.x + xInc, center.y + yInc, center.z)); // upper right

	init();
}

// Opposite sides are parallel 
Plane::Plane(const glm::vec3& min, const glm::vec3& max)
{
	_vertices.push_back(min);								// lower left
	_vertices.push_back(min + glm::vec3(0, max.y, 0));		// upper left
	_vertices.push_back(max - glm::vec3(0, min.y, 0));		// lower right
	_vertices.push_back(max);								// upper right

	init();
}

void Plane::render()
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Plane::init()
{
	glm::vec3 normal = glm::normalize(glm::cross(_vertices[3] - _vertices[2], _vertices[0] - _vertices[2]));
	_normals.insert(_normals.end(), 4, normal);

	_textureCoords.push_back(glm::vec2(0, 0));
	_textureCoords.push_back(glm::vec2(0, 1));
	_textureCoords.push_back(glm::vec2(1, 0));
	_textureCoords.push_back(glm::vec2(1, 1));

	int arr[] = { 0, 3, 1, 0, 2, 3 };
	_indices.insert(_indices.end(), std::begin(arr), std::end(arr));

	GLuint vbo, nbo, ebo;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
