#include "Camera.h"


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
	return _projectionMatrix *_viewMatrix;
}

