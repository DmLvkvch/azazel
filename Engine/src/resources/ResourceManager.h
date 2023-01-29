#pragma once

#include <unordered_map>
#include <string>
#include <renderer/Shader.h>
#include <renderer/Texture.h>

namespace Azazel
{
    template <typename T>
    class ResourceManager
    {
    private:
        std::unordered_map<std::string, T> resources;   
    };
}