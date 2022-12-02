#include "Camera.h"

#include <iostream>

namespace Azazel
{

	Camera::Camera()
	{
		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Camera::~Camera()
	{
		
	}

	void Camera::setPosition(glm::vec3 position)
	{

	}

	void Camera::setScale(glm::vec3 scale)
	{

	}

	void Camera::setRotation(glm::vec3 rotation)
	{

	}

	void Camera::setDirection(glm::vec3 direction)
	{

	}
	
	void Camera::moveForward(float z)
	{
		this->position = this->position + glm::vec3(0.0f, 0.0f, z);
	}

	void Camera::moveRight(float x)
	{
		this->position = this->position + glm::vec3(x, 0.0f, 0.0f);
	}

	void Camera::moveUp(float y)
	{
		this->position = this->position + glm::vec3(0.0f, y, 0.0f);
	}

	void Camera::setLookAtPosition(glm::vec3 lookAtPosition)
	{
		
	}

	glm::mat4 Camera::getViewLookAtMatrix(glm::vec3 up)
	{
		return glm::lookAt(glm::vec3{1.0f, 1.0f, 1.0f}, lookAtPosition, up);
	}

	glm::vec3& Camera::getPosition()
	{
		return this->position;
	}
}