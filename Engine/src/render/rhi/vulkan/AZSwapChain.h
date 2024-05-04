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
        ~AZSwapChain();

        void destroy();
        uint32_t acquireNextImage(VkSemaphore signalSemaphore) const;
        void recreate(uint32_t width, uint32_t height);

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        VkSurfaceFormatKHR surfaceFormat;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        VkPresentModeKHR presentMode;
        
        VkImageView depthImageView;
        VkDeviceMemory depthImageMemory;
        VkImage depthImage;
        uint32_t imageCount;

        void initSwapChainFramebuffers(AZRenderPass& renderPass);
    private:
        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface);
        std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format);
        VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    
    private:
        VulkanDevice& device;
        PhysicalDevice& physicalDevice;
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