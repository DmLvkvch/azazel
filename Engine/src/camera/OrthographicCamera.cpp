#include "OrthographicCamera.h"
#include <iostream>
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
            this->projectionMatrix = glm::ortho(left, right , bottom, top, near, far);
            this->rotation = 0.0;
            this->position = glm::vec3 {0.0f, 0.0f, 0.0f};
            this->ortho = {left, right, bottom, top};
            this->scale = {1.0, 1.0, 1.0};
            this->zoomFactor = 1.0f;
            updateMatrix();
        }
        
        void OrthographicCamera::updateMatrix()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0), position);
            transform = glm::rotate(transform, rotation, glm::vec3{0.0f, 0.0f, 1.0f});
            viewMatrix = glm::inverse(transform);
            this->projectionMatrix = glm::ortho(zoomFactor * ortho.x, zoomFactor * ortho.y, zoomFactor * ortho.z, zoomFactor * ortho.w, -1.0f, 1.0f);

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

        void OrthographicCamera::zoom(const glm::vec2& zoom, const glm::vec2& origin)
        {
            updateMatrix();
        }
}