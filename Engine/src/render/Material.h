#pragma once

#include <glm/vec3.hpp>
#include "Texture.h"

namespace Azazel
{
    struct Material
    {
        glm::vec3 diffuse;
        glm::vec3 ambient;
        glm::vec3 specular;
        float shininess;
    };

    struct MaterialMap
    {
        Texture* diffuse;
        Texture* specular;
        Texture* normalMap;
        float specular;
        float shininess;
    };
}