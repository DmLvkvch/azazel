#include "Camera.h"

#include <iostream>

namespace Azazel
{

    Camera::Camera()
    {
    }

    Camera::~Camera()
    {
        
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        camera.position = position;
    }

    void Camera::setDirection(const glm::vec3& direction)
    {

    }

    void Camera::moveRight(float x)
    {
        camera.position += glm::vec3(x, 0.0f, 0.0f);
    }

    void Camera::moveUp(float y)
    {
        camera.position += glm::vec3(0.0f, y, 0.0f);
    }

    void Camera::moveForward(float z)
    {
        camera.position += glm::vec3(0.0f, 0.0f, z);
    }

    void Camera::setLookAtPosition(const glm::vec3& lookAtPosition)
    {
    }

    glm::mat4 Camera::getViewLookAtMatrix(glm::vec3 lookAtPosition)
    {
        return glm::lookAt(camera.position, lookAtPosition, camera.up);
    }

    void Camera::move(const glm::vec3& move)
    {
        this->camera.position += move;
    }
}