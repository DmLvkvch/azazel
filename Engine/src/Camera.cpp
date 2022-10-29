#include "Camera.h"

#include <iostream>

namespace Azazel
{

	Camera::Camera()
	{
		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	void Camera::setPosition(glm::vec3 position)
	{

	}

	void Camera::setScale(glm::vec3 scale)
	{

	}

	void Camera::setRotation(glm::vec3 rotation)
	{
		if (this->rotation == rotation)
			return;
		this->position = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x),glm::vec3(-1.0f, 0.0f, 0.0f)) * glm::vec4(this->position, 1.0f));
		this->rotation = rotation;
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
	glm::mat4 Camera::getViewMatrix()
	{
		return glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
}