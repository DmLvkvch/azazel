#include "OrthographicCamera.h"
#include <iostream>
namespace Azazel
{
        OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : position(0.0f, 0.0f, 0.0f), rotation(0.0f), scale(0.0f) 
        {
            this->projectionMatrix = glm::ortho(left, right, bottom, top, -1000.0f, 1000.0f);
            this->rotation = 0.0;
            this->position = glm::vec3 {0.0f, 0.0f, 0.0f};
            this->scale = glm::vec3 {1.0f, 1.0f, 1.0f};
        }
        
        void OrthographicCamera::updateMatrix()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0), position);
            transform = glm::rotate(transform, rotation, glm::vec3{0.0f, 0.0f, 1.0f});
            glm::vec3 tmp = 1.0f / scale;
            transform = glm::scale(transform , tmp);
            viewMatrix = glm::inverse(transform);
            viewProjectionMatrix = projectionMatrix * viewMatrix;
        }

        OrthographicCamera::~OrthographicCamera()
        {

        }

        void OrthographicCamera::setPosition(glm::vec2& position)
        {
            this->position.x = position.x;
            this->position.y = position.y;
            updateMatrix();
        }

        void OrthographicCamera::setPosition(float x, float y)
        {
            glm::vec2 tmp {x, y};
            setPosition(tmp);
        }

        void OrthographicCamera::setRotation(float a)
        {
            this->rotation = a;
            updateMatrix();
        }

        void OrthographicCamera::move(float x, float y)
        {
            glm::vec2 tmp {x, y};
            move(tmp);
        }

        void OrthographicCamera::move(glm::vec2& dist)
        {
            setPosition(position.x + dist.x, position.y + dist.y);
        }

        void OrthographicCamera::setScale(glm::vec2& scale)
        {
            this->scale.x += scale.x;
            this->scale.y += scale.y;
            std::cout << this->scale.x << this->scale.y<<std::endl;
            updateMatrix();
        }

        void OrthographicCamera::setScale(float x, float y)
        {
            glm::vec2 tmp {x, y};
            setScale(tmp);
        }
}