#include "OrthographicCamera.h"
#include <iostream>
namespace Azazel
{
        OrthographicCamera::OrthographicCamera()
        : OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f)
        {

        }

        OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : position(0.0f, 0.0f, 0.0f), rotation(0.0f), scale(0.0f) 
        {
            this->projectionMatrix = glm::ortho(left, right, bottom, top, -1000.0f, 1000.0f);
            this->rotation = 0.0;
            this->position = glm::vec3 {0.0f, 0.0f, 0.0f};
            this->scale = glm::vec3 {1.0f, 1.0f, 1.0f};
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

        void OrthographicCamera::move(const glm::vec2& dist)
        {
            setPosition({position.x + dist.x, position.y + dist.y});
        }

        void OrthographicCamera::setScale(const glm::vec2& scale)
        {
            this->scale.x += scale.x;
            this->scale.y += scale.y;
            updateMatrix();
        }
}