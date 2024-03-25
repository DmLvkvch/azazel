#pragma once

#include "AZInstance.h"
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

        AZSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);

        ~AZSwapChain()
        {

        }

        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device);

        std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

        uint32_t acquireNextImage()
        {
            return 0;
        }

        void recreate()
        {
        }

        VkSwapchainKHR swapChain;

        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        VkSurfaceFormatKHR surfaceFormat;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
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