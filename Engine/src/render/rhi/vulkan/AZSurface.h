#pragma once
#include "vk_headers.h"

#include <GLFW/glfw3.h>

namespace Azazel
{
    class AZSurface
    {
    public:
        VkSurfaceKHR createSurface(VkInstance& instance, GLFWwindow* window);

        VkSurfaceKHR surface;
    };
}