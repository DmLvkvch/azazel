#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    class Camera
    {
    private:
        glm::vec3 position {0.0f, 0.0f, 1.0f};
        glm::vec3 lookAtPosition {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 direction;

        glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
    public:

        Camera();
        
        ~Camera();

        void setPosition(glm::vec3 position);
        
        void setScale(glm::vec3 scale);
        
        void setRotation(glm::vec3 rotation);

        void setDirection(glm::vec3 direction);

        void moveForward(float z);

        void moveRight(float x);

        void moveUp(float y);

        void setLookAtPosition(glm::vec3 lookAtPosition = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 getViewLookAtMatrix(glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

        glm::vec3& getPosition();
    };
}