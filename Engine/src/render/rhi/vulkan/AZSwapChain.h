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

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<AZFramebuffer> swapChainFramebuffers;

        vk::SurfaceFormatKHR surfaceFormat;
        vk::Format swapChainImageFormat;
        vk::Extent2D swapChainExtent;
        vk::PresentModeKHR presentMode;
        
        VkImageView depthImageView;
        VkDeviceMemory depthImageMemory;
        VkImage depthImage;
        uint32_t imageCount;

        void initSwapChainFramebuffers(AZRenderPass& renderPass);
    private:
        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface);
        std::vector<VkImageView> createImageViews(vk::Device device, std::vector<vk::Image>& swapChainImages, VkFormat format);
        VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR choosePresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
        VkExtent2D chooseExtent(GLFWwindow* window, const vk::SurfaceCapabilitiesKHR& capabilities);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    
    private:
        VulkanDevice& device;
        PhysicalDevice& physicalDevice;
    };

    struct VirtualFrame
    {
        vk::Fence commandQueueFence;
    };

    class VirtualFrameProvider
    {
        std::vector<VirtualFrame> virtualFrames;
        uint32_t presentImageIndex = 0;
        bool frameRunning = false;
        size_t currentFrame = 0;
    public:
        void init(size_t frameCount, size_t stageBufferSize);
        void destroy();

        void startFrame();
        VirtualFrame& getCurrentFrame();
        VirtualFrame& getNextFrame();
        const VirtualFrame& getCurrentFrame() const;
        const VirtualFrame& getNextFrame() const;
        uint32_t getPresentImageIndex() const;
        bool isFrameRunning() const;
        size_t getFrameCount() const;
        void endFrame();
    };
}