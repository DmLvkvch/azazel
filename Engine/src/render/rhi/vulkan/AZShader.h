#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZShader
    {
    public:

        AZShader()
        {

        }

        AZShader(const std::string& vertexShader, const std::string& fragmentShader);

        ~AZShader();

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
    };
}