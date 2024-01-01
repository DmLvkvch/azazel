#pragma once

#include "VKContext.h"
#include "AZSurface.h"
#include "AZDevice.h"


namespace Azazel
{
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class GLFWWindow;

    class AZSwapChain
    {
    public:

        AZSwapChain()
        {

        }

        AZSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);

        ~AZSwapChain()
        {

        }

        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);

        std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, AZSurface& azSurface);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

        uint32_t acquireNextImage()
        {
            
        }

        void recreate()
        {

        }

        VkSwapchainKHR swapChain;

        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    };
}