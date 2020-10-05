#include "Camera.h"
#include "glm/gtx/quaternion.hpp"

Camera:: Camera(const glm::vec3& eye, const glm::vec3& direction, int width, int height, float fov, float nearClip, float farClip) :
_eye(eye), _direction(direction), _width(width), _height(height), _vFoV(fov), _nearClip(nearClip), _farClip(farClip)
{
	if (height <= 0 || width <= 0)
	{
		_width = 800;
		_height = 600;
		std::cerr << "CAMERA WARNING: Width or height not greater 0. Default width(800) and height(600) are taken.\n";
	}
	_aspect = (float)_width / (float)_height;

	updateViewMatrix();
	updateProjectionMatrix();
	updateNormalMatrix();

}

const glm::mat4& Camera::getViewMatrix()
{
	return _viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}

const glm::mat4& Camera::getViewProjectionMatrix()
{
	glm::mat4 viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	return viewProjectionMatrix;
}

const glm::mat3& Camera::getNormalMatrix()
{
	return _normalMatrix;
}

void Camera::move(const glm::vec3& v)
{
	glm::vec4 viewSpaceTrans = _viewMatrix * glm::vec4(v, 0.0);
	_eye += glm::vec3(viewSpaceTrans);
	updateViewMatrix();
}


void Camera::rotate(const glm::vec3& rotAxis, const float angle)
{
	glm::quat rotationQuat = glm::angleAxis(angle, glm::normalize(rotAxis));
	_direction = glm::rotate(rotationQuat, _direction);
	updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	_viewMatrix = glm::lookAt(_eye, _eye + _direction, glm::vec3(0, 1, 0));
}

void Camera::updateProjectionMatrix()
{
	_projectionMatrix = glm::perspective(glm::radians(_vFoV), _aspect, _nearClip, _farClip);
}

void Camera::updateNormalMatrix()
{
	_normalMatrix = glm::inverseTranspose(glm::mat3(_viewMatrix));
}

