#include "Cube.h"

// Axis aligned plane (xy plane)
Cube::Cube(const glm::vec3& center, const float width, const float height, const float depth)
{
	float xInc = width / 2.0f;
	float yInc = height / 2.0f;
	float zInc = depth / 2.0f;
	_vertices.push_back(glm::vec3(center.x - xInc, center.y + yInc, center.z - depth)); // top 0
	_vertices.push_back(glm::vec3(center.x + xInc, center.y + yInc, center.z - depth)); // top 1
	_vertices.push_back(glm::vec3(center.x + xInc, center.y + yInc, center.z + depth)); // top 2
	_vertices.push_back(glm::vec3(center.x - xInc, center.y + yInc, center.z + depth)); // top 3

	_vertices.push_back(glm::vec3(center.x - xInc, center.y - yInc, center.z - depth)); // bottom 4
	_vertices.push_back(glm::vec3(center.x + xInc, center.y - yInc, center.z - depth)); // bottom 5
	_vertices.push_back(glm::vec3(center.x + xInc, center.y - yInc, center.z + depth)); // bottom 6
	_vertices.push_back(glm::vec3(center.x - xInc, center.y - yInc, center.z + depth)); // bottom 7

	init();
}

// Opposite sides are parallel 
Cube::Cube(const glm::vec3& min, const glm::vec3& max)
{
	glm::vec3 diff = max - min;
	_vertices.push_back(min + glm::vec3(0, diff.y ,0)); // top 0
	_vertices.push_back(max - glm::vec3(0, 0, diff.z)); // top 1
	_vertices.push_back(max);							// top 2
	_vertices.push_back(max - glm::vec3(diff.x, 0, 0)); // top 3

	_vertices.push_back(min);							// bottom 4
	_vertices.push_back(min + glm::vec3(diff.x, 0 ,0)); // bottom 5
	_vertices.push_back(max - glm::vec3(0, diff.y ,0)); // bottom 6
	_vertices.push_back(min + glm::vec3(0, 0, diff.z)); // bottom 7

	init();
}

void Cube::render()
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Cube::init()
{
	int arr[] = {	0, 1, 2, // top
					0, 2, 3,

					3, 2, 6, // back
					3, 6, 7,
	
					7, 6, 5, // bottom 
					7, 5, 4,
	
					4, 5, 1, // front
					4, 1, 0,
	
					5, 6, 2, // right
					5, 2, 1,
	
					4, 0, 3, // left
					4, 3, 7 };

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
