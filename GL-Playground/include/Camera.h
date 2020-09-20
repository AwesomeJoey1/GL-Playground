#pragma once
#include "Common.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

class Camera {
public:
	Camera(const glm::vec3& eye, const glm::vec3& direction, int width, int height, float fov=45.0f, float nearClip=0.1f, float farClip=100.0f) : 
		_eye(eye), _direction(direction), _width(width), _height(height),_vFoV(fov), _nearClip(nearClip), _farClip(farClip) 
	{	
		if (height <= 0 || width <= 0)
		{
			_width = 800;
			_height = 600;
			std::cerr << "CAMERA WARNING: Width or height not greater 0. Default width(800) and height(600) are taken.\n";
		}
		_aspect = (float)_width / (float)_height;

		_viewMatrix = glm::lookAt(_eye, glm::vec3(0), glm::vec3(0, 1, 0));
		_projectionMatrix = glm::perspective(glm::radians(_vFoV), _aspect, _nearClip, _farClip);
		_normalMatrix = glm::inverseTranspose(glm::mat3(_viewMatrix));
			
	}

	const glm::mat4& getProjectionMatrix();
	const glm::mat4& getViewMatrix();
	const glm::mat4& getViewProjectionMatrix();
	const glm::mat3& getNormalMatrix();

private:
	glm::vec3 _eye, _direction;
	float _vFoV, _nearClip, _farClip, _aspect;
	int _width, _height;
	glm::mat4 _viewMatrix, _projectionMatrix;
	glm::mat3 _normalMatrix;
};