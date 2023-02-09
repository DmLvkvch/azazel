#include "OrthographicCamera.h"

namespace Azazel
{
    OrthographicCamera::OrthographicCamera()
    : OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f)
    {
    }

    OrthographicCamera::OrthographicCamera(float width, float height)
    : OrthographicCamera(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1.0f, 1.0f)
    {
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    {
        this->projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
        this->position = glm::vec3{0.0f, 0.0f, 0.0f};
        this->near = near;
        this->far = far;
        updateMatrix();
    }
    
    void OrthographicCamera::updateMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position);
        transform = glm::rotate(transform, rotation, glm::vec3{0.0f, 0.0f, 1.0f});
        viewMatrix = glm::inverse(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::setPosition(const glm::vec2& position)
    {
        this->position.x = position.x;
        this->position.y = position.y;
        updateMatrix();
    }

    void OrthographicCamera::move(const glm::vec2& dist)
    {
        setPosition({position.x + dist.x, position.y + dist.y});
    }

    void OrthographicCamera::setRotation(float rotation)
    {
        this->rotation = rotation;
        updateMatrix();
    }

    void OrthographicCamera::rotate(float rotation)
    {
        this->rotation += rotation;
        updateMatrix();
    }
    
    void OrthographicCamera::zoom(const glm::vec2& zoom, const glm::vec2& origin)
    {
        updateMatrix();
    }
}