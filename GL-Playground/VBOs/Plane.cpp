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
}

void Plane::render()
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Plane::init()
{
	int arr[] = { 0, 3, 1, 0, 2, 3 };
	_indices.insert(_indices.end(), std::begin(arr), std::end(arr));

	GLuint vbo, ebo;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
