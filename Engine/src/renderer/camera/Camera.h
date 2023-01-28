#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    struct CameraLocation
    {
        glm::vec3 position { 0.0f, 0.0f, 0.0f };
        glm::vec3 direction { 0.0f, 0.0f, -1.0f };
        glm::vec3 up { 0.0f, 1.0f, 0.0f };
    };

    class Camera
    {
    public:

        Camera();

        ~Camera();

        void setPosition(const glm::vec3& position);

        void setDirection(const glm::vec3& direction);

        void moveForward(float z);

        void moveRight(float x);

        void moveUp(float y);

        void setLookAtPosition(const glm::vec3& lookAtPosition = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 getViewLookAtMatrix(glm::vec3 lookAtPosition = glm::vec3{0.0, 0.0, 0.0});

        inline const glm::vec3& getImmutablePosition() const
        {
            return camera.position;
        }

        void move(const glm::vec3& move);
    private:
        CameraLocation camera;
    };
}