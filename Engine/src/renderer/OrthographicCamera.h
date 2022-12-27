#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera();
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        void setPosition(const glm::vec2& position);
        void setRotation(float rotation);
        void rotate(float deltaAngle);

        void setScale(const glm::vec2& scale);
        void move(const glm::vec2& dist);
        const glm::mat4& getViewMatrix() const { return viewMatrix; }
        const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }

    private:
        void updateMatrix();
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;

        glm::vec3 position;
        glm::vec3 scale;
        float rotation;
    };
}
