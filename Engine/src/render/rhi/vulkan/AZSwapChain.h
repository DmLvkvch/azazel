#pragma once

#include "AZInstance.h"
#include "AZSurface.h"
#include "AZDevice.h"
#include "AZFramebuffer.h"
#include "AZRenderPass.h"

namespace Azazel
{
    struct SwapChainSupportDetails
    {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class GLFWWindow;

    class AZSwapChain
    {
    public:

        AZSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);
        ~AZSwapChain();

        void destroy();
        uint32_t acquireNextImage(VkSemaphore signalSemaphore) const;
        void recreate(uint32_t width, uint32_t height);

        vk::SwapchainKHR swapChain;
        std::vector<vk::Image> swapChainImages;
        std::vector<vk::ImageView> swapChainImageViews;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        vk::SurfaceFormatKHR surfaceFormat;
        vk::Format swapChainImageFormat;
        vk::Extent2D swapChainExtent;
        vk::PresentModeKHR presentMode;
        
        vk::ImageView depthImageView;
        vk::DeviceMemory depthImageMemory;
        vk::Image depthImage;
        uint32_t imageCount;

        void initSwapChainFramebuffers(AZRenderPass& renderPass);
    private:
        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface);
        std::vector<vk::ImageView> createImageViews(vk::Device device, std::vector<vk::Image>& swapChainImages, vk::Format format);
        vk::SurfaceFormatKHR chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
        vk::PresentModeKHR choosePresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
        vk::Extent2D chooseExtent(GLFWwindow* window, const vk::SurfaceCapabilitiesKHR& capabilities);

        vk::ImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags);

        void createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory);
    
    private:
        VulkanDevice& device;
        PhysicalDevice& physicalDevice;
    };
}