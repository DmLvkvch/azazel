#pragma once

#include "render/Shader.h"
#include <unordered_map>

namespace Azazel
{
    class AZShader
    {
    public:

        AZShader(const std::string& vertexShader, const std::string& fragmentShader);

        ~AZShader();
    };
}