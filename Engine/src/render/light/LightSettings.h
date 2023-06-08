#pragma once

#include <glm/vec3.hpp>

namespace Azazel
{
    class LightSettings
    {
        glm::vec3 diffuse;
        glm::vec3 ambient;
        glm::vec3 specular;
        glm::vec3 position;
    };
}