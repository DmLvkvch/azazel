#include "AZSurface.h"
#include "AZSwapChain.h"

namespace Azazel
{
    AZSurface::AZSurface(vk::Instance& instance, GLFWwindow* window)
    {
        surface = vk::SurfaceKHR { createSurface(instance, window) };
    }

    vk::SurfaceKHR AZSurface::createSurface(vk::Instance& instance, GLFWwindow* window)
    {
        VkSurfaceKHR surface;
        glfwCreateWindowSurface(instance, window, nullptr, &surface);
        return vk::SurfaceKHR {surface};
    }

    SwapChainSupportDetails AZSurface::querySwapChainSupport(vk::PhysicalDevice& physicalDevice)
    {
        SwapChainSupportDetails details;
        details.capabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
        details.formats = physicalDevice.getSurfaceFormatsKHR(surface);
        details.presentModes = physicalDevice.getSurfacePresentModesKHR(surface);
        return details;
    }
}