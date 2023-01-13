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
        OrthographicCamera(float width, float height);
        OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
        ~OrthographicCamera();

        void setPosition(const glm::vec2& position);
        void setRotation(float rotation);
        void rotate(float deltaAngle);

        void move(const glm::vec2& dist);
        const glm::mat4& getViewMatrix() const { return viewMatrix; }
        const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }

        void zoom(const glm::vec2& zoom, const glm::vec2& origin = glm::vec2 {0.0f, 0.0f});

    private:
        void updateMatrix();
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;

        float zoomFactor;
        glm::vec3 scale;
        glm::vec4 ortho;
        glm::vec3 position;
        float rotation;
    };
}
