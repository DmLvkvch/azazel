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
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class GLFWWindow;

    class AZSwapChain
    {
    public:

        AZSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);

        ~AZSwapChain()
        {

        }

        uint32_t acquireNextImage(VkSemaphore signalSemaphore) const
        {
            uint32_t imageIndex;
            vkAcquireNextImageKHR(device.device, swapChain, UINT64_MAX, signalSemaphore, VK_NULL_HANDLE, &imageIndex);
            return imageIndex;
        }

        void recreate(uint32_t width, uint32_t height)
        {
        }

        void cleanupSwapChain() 
        {
            for (auto& framebuffer : swapChainFramebuffers) 
            {
                vkDestroyFramebuffer(device.device, framebuffer.framebuffer, nullptr);
            }

            for (auto imageView : swapChainImageViews) 
            {
                vkDestroyImageView(device.device, imageView, nullptr);
            }

            vkDestroySwapchainKHR(device.device, swapChain, nullptr);
        }

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        VkSurfaceFormatKHR surfaceFormat;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        void initSwapChainFramebuffers(AZRenderPass& renderPass)
        {
            swapChainFramebuffers.resize(swapChainImageViews.size());
            for (size_t i = 0; i < swapChainImageViews.size(); i++)
            {
                uint32_t width = swapChainExtent.width;
                uint32_t height = swapChainExtent.height;
                auto& imageView = swapChainImageViews[i];
                AZFramebufferDesc fboDesc{ {imageView}, renderPass.renderPass, width, height };
                swapChainFramebuffers[i] = AZFramebuffer(device.device, fboDesc);
            }
        }
    private:
        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);
        std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
    public:
    
    private:
        VulkanDevice& device;
    };

    struct VirtualFrame
    {
    };

    class VirtualFrameProvider
    {
        std::vector<VirtualFrame> virtualFrames;
        uint32_t presentImageIndex = 0;
        bool isFrameRunning = false;
        size_t currentFrame = 0;
    public:
        void Init(size_t frameCount, size_t stageBufferSize);
        void Destroy();

        void StartFrame();
        VirtualFrame& GetCurrentFrame();
        VirtualFrame& GetNextFrame();
        const VirtualFrame& GetCurrentFrame() const;
        const VirtualFrame& GetNextFrame() const;
        uint32_t GetPresentImageIndex() const;
        bool IsFrameRunning() const;
        size_t GetFrameCount() const;
        void EndFrame();
    };
}