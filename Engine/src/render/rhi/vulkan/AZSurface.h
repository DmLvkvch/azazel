#pragma once
#include "vk_headers.h"

#include <GLFW/glfw3.h>

namespace Azazel
{
    class SwapChainSupportDetails;

    class AZSurface
    {
    public:
        AZSurface(vk::Instance& instance, GLFWwindow* window);

        SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice& physicalDevice);

        vk::SurfaceKHR createSurface(vk::Instance& instance, GLFWwindow* window);

        vk::SurfaceKHR surface;
    };
}