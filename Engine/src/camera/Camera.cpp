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
        cameraLocation.position = position;
    }

    void Camera::setDirection(const glm::vec3& direction)
    {

    }

    void Camera::moveRight(float x)
    {
        cameraLocation.position += glm::vec3(x, 0.0f, 0.0f);
    }

    void Camera::moveUp(float y)
    {
        cameraLocation.position += glm::vec3(0.0f, y, 0.0f);
    }

    void Camera::moveForward(float z)
    {
        cameraLocation.position += glm::vec3(0.0f, 0.0f, z);
    }

    void Camera::setLookAtPosition(const glm::vec3& lookAtPosition)
    {
    }

    glm::mat4 Camera::getViewLookAtMatrix(glm::vec3 lookAtPosition)
    {
        return glm::lookAt(cameraLocation.position, lookAtPosition, cameraLocation.up);
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(cameraLocation.position, cameraLocation.position + cameraLocation.direction, cameraLocation.up);
    }

    void Camera::move(const glm::vec3& move)
    {
        this->cameraLocation.position += move;
    }

    void Camera::updateCamera()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->front = glm::normalize(front);
        right = glm::normalize(glm::cross(this->front, glm::vec3{0.0f, 1.0f, 0.0f}));
        cameraLocation.up    = glm::normalize(glm::cross(right, this->front));
    }
}