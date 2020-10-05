#pragma once
#include "Common.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

class Camera {
public:
	Camera(const glm::vec3& eye, const glm::vec3& direction, int width, int height, float fov = 45.0f, float nearClip = 0.1f, float farClip = 100.0f);

	const glm::mat4& getProjectionMatrix();
	const glm::mat4& getViewMatrix();
	const glm::mat4& getViewProjectionMatrix();
	const glm::mat3& getNormalMatrix();

	void move(const glm::vec3& v);
	void rotate(const glm::vec3& rotAxis, const float angle);

private:
	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateNormalMatrix();
	glm::vec3 _eye, _direction;
	float _vFoV, _nearClip, _farClip, _aspect;
	int _width, _height;
	glm::mat4 _viewMatrix, _projectionMatrix;
	glm::mat3 _normalMatrix;
};