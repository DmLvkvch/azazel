#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    struct CameraProjection
    {
        float fov;
        float width;
        float height;
        float near;
        float far;
    };

    struct CameraLocation
    {
        glm::vec3 position { 0.0f, 0.0f, 0.0f };
        glm::vec3 direction { 0.0f, 0.0f, -1.0f };
        glm::vec3 up { 0.0f, 1.0f, 0.0f };
    };

    class Camera
    {
    public:

        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float zoom;
        glm::vec3 right;
        glm::vec3 front;

        Camera();

        ~Camera();

        void setPosition(const glm::vec3& position);

        void setDirection(const glm::vec3& direction);

        void moveForward(float z);

        void moveRight(float x);

        void moveUp(float y);

        void setLookAtPosition(const glm::vec3& lookAtPosition = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 getViewLookAtMatrix(glm::vec3 lookAtPosition = glm::vec3{0.0, 0.0, 0.0});

        glm::mat4 getViewMatrix();

        inline const glm::vec3& getImmutablePosition() const
        {
            return cameraLocation.position;
        }

        void move(const glm::vec3& move);

        void zoomCamera(float offset)
        {
            this->zoom -= (float)offset;
            if (this->zoom < 1.0f)
                this->zoom = 1.0f;
            if (this->zoom > 45.0f)
                this->zoom = 45.0f;
        }
    private:
        void updateCamera();
        CameraLocation cameraLocation;
    };
}