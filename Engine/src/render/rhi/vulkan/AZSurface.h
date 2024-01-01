#pragma once
#include "vk_headers.h"

#include <GLFW/glfw3.h>


namespace Azazel
{
    class AZSurface
    {
    public:
        AZSurface(VkInstance& instance, GLFWwindow* window)
        {
            surface = createSurface(instance, window);
        }

        VkSurfaceKHR createSurface(VkInstance& instance, GLFWwindow* window);

        VkSurfaceKHR surface;
    };
}