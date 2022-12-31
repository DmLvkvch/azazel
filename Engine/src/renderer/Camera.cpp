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

    void Camera::setPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    void Camera::setScale(const glm::vec3& scale)
    {

    }

    void Camera::setRotation(const glm::vec3& rotation)
    {
        this->rotation = rotation;
    }

    void Camera::setDirection(const glm::vec3& direction)
    {

    }

    void Camera::moveRight(float x)
    {
        this->position += glm::vec3(x, 0.0f, 0.0f);
    }

    void Camera::moveUp(float y)
    {
        this->position += glm::vec3(0.0f, y, 0.0f);
    }

    void Camera::moveForward(float z)
    {
        this->position += glm::vec3(0.0f, 0.0f, z);
    }

    void Camera::setLookAtPosition(const glm::vec3& lookAtPosition)
    {
        this->lookAtPosition = lookAtPosition;
    }

    glm::mat4 Camera::getViewLookAtMatrix(const glm::vec3& up)
    {
        return glm::lookAt(position, position + cameraFront, cameraUp);
    }

    const glm::vec3& Camera::getPosition()
    {
        return this->position;
    }

    void Camera::move(const glm::vec3& move)
    {
        this->position = this->position + move;
    }
}