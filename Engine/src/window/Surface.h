#pragma once

#include <vulkan/vulkan.hpp>

namespace Azazel
{
    class Surface
    {
    
    	Surface()
        {
            if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) 
            {
                throw std::runtime_error("failed to create window surface!");
            }
        }
        
        ~Surface()
        {
	        vkDestroySurfaceKHR(instance, surface, nullptr);
        }

        operator const VkSurfaceKHR &() const { return surface; }

        const VkSurfaceKHR &GetSurface() const { return surface; }
        const VkSurfaceCapabilitiesKHR &GetCapabilities() const { return capabilities; }
        const VkSurfaceFormatKHR &GetFormat() const { return format; }

    private:
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        VkSurfaceCapabilitiesKHR capabilities {};
        VkSurfaceFormatKHR format {};
    };
}