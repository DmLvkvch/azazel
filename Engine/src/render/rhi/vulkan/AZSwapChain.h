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
        VkPresentModeKHR presentMode;
        
        VkImageView depthImageView;
        VkDeviceMemory depthImageMemory;
        VkImage depthImage;
        uint32_t imageCount;

        void initSwapChainFramebuffers(AZRenderPass& renderPass);
    private:
        VkSwapchainKHR createSwapChain(GLFWwindow* window, AZSurface& surface);
        std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) 
        {
            VkImageCreateInfo imageInfo {};
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.extent = { width, height, 1 };
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.format = format;
            imageInfo.tiling = tiling;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageInfo.usage = usage;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            vkCreateImage(device.device, &imageInfo, nullptr, &image);

            VkMemoryRequirements memRequirements;
            vkGetImageMemoryRequirements(device.device, image, &memRequirements);

            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memRequirements.size;
            allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

            vkAllocateMemory(device.device, &allocInfo, nullptr, &imageMemory);
            vkBindImageMemory(device.device, image, imageMemory, 0);
        }
    
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