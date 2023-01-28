#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    struct Transform
    {
        glm::vec3 position {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation {0.0f, 0.0f, 0.0f};
        glm::vec3 scale    {1.0f, 1.0f, 1.0f};
        
        glm::mat4 getTransformMatrix()
        {
            glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);
            glm::mat4 R(1.0f);
            R = glm::rotate(R, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f,  0.0f));
            R = glm::rotate(R, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f,  0.0f));
            R = glm::rotate(R, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
            glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
            return T * R * S;
        }
    };
}