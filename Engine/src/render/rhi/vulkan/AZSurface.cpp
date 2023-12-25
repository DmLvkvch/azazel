#include "AZSurface.h"

namespace Azazel
{
    VkSurfaceKHR AZSurface::createSurface(VkInstance& instance, GLFWwindow* window)
    {
        glfwCreateWindowSurface(instance, window, nullptr, &surface);
        return surface;
    }
}