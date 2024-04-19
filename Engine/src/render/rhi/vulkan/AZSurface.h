#pragma once
#include "vk_headers.h"

#include <GLFW/glfw3.h>

namespace Azazel
{
    class SwapChainSupportDetails;

    class AZSurface
    {
    public:
        AZSurface(VkInstance& instance, GLFWwindow* window);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        VkSurfaceKHR createSurface(VkInstance& instance, GLFWwindow* window);

        VkSurfaceKHR surface;
    };
}