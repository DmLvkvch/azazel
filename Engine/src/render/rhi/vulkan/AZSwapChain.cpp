#include "AZSwapChain.h"

#include <cmath>
#include "AZImage.h"


namespace Azazel
{
    AZSwapChain::AZSwapChain(GLFWwindow* window, AZSurface& surface, PhysicalDevice& physicalDevice, VulkanDevice& device)
    : device(device), physicalDevice(physicalDevice)
    {
        this->swapChain = createSwapChain(window, surface);
        this->swapChainImageViews = createImageViews(device.device, swapChainImages, swapChainImageFormat);
    }

    AZSwapChain::~AZSwapChain()
    {
        destroy();
    }

    void AZSwapChain::destroy()
    {
        vkDestroyImageView(device.device, depthImageView, nullptr);
        vkDestroyImage(device.device, depthImage, nullptr);
        vkFreeMemory(device.device, depthImageMemory, nullptr);

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

    uint32_t AZSwapChain::acquireNextImage(VkSemaphore signalSemaphore) const
    {
        uint32_t imageIndex = device.device.acquireNextImageKHR(swapChain, UINT64_MAX, signalSemaphore).value;
        return imageIndex;
    }

    void AZSwapChain::recreate(uint32_t width, uint32_t height)
    {
    }

    VkSwapchainKHR AZSwapChain::createSwapChain(GLFWwindow* window, AZSurface& surface)
    {
        VkSwapchainKHR swapChain;
        SwapChainSupportDetails swapChainSupport = surface.querySwapChainSupport(physicalDevice.get());
        surfaceFormat   = chooseSurfaceFormat(swapChainSupport.formats);
        presentMode     = choosePresentMode(swapChainSupport.presentModes);
        swapChainExtent = chooseExtent(window, swapChainSupport.capabilities);

        imageCount = std::min(swapChainSupport.capabilities.maxImageCount, swapChainSupport.capabilities.minImageCount + 1);
        vk::SwapchainCreateInfoKHR createInfo {};

        createInfo.setSurface(surface.surface).setMinImageCount(imageCount)
                  .setImageFormat(surfaceFormat.format).setImageColorSpace(surfaceFormat.colorSpace)
                  .setImageExtent(swapChainExtent).setImageArrayLayers(1)
                  .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
        auto& indices = physicalDevice.getQueueFamilyIndices();
        auto queueFamilyIndices = indices.getIndices();

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.setImageSharingMode(vk::SharingMode::eConcurrent)
                      .setQueueFamilyIndices({2, queueFamilyIndices.data()});
        }
        else
        {
            createInfo.setImageSharingMode(vk::SharingMode::eExclusive);
        }
        createInfo.setPreTransform(swapChainSupport.capabilities.currentTransform)
                  .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
                  .setPresentMode(presentMode)
                  .setClipped(VK_TRUE)
                  .setOldSwapchain({});

        swapChain = device.device.createSwapchainKHR(createInfo);
        swapChainImages = device.device.getSwapchainImagesKHR(swapChain);
        swapChainImageFormat = surfaceFormat.format;
        return swapChain;
    }

    vk::ImageView AZSwapChain::createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags)
    {
        vk::ImageViewCreateInfo createInfo {};
        vk::ImageSubresourceRange subResourceRange {};
        subResourceRange.setAspectMask(aspectFlags).setBaseMipLevel(0).setLevelCount(1).setBaseArrayLayer(0).setLayerCount(1);
        vk::ComponentMapping componentMapping {};
        createInfo.setImage(image).setViewType(vk::ImageViewType::e2D).setFormat(format).setComponents(componentMapping).setSubresourceRange(subResourceRange);
        return device.device.createImageView(createInfo);
    }

    void AZSwapChain::createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory)
    {
        vk::ImageCreateInfo imageCreateInfo {};
        imageCreateInfo.setImageType(vk::ImageType::e2D).setExtent({width, height, 1}).setMipLevels(1)
                       .setArrayLayers(1).setFormat(format).setTiling(tiling).setInitialLayout(vk::ImageLayout::eUndefined)
                       .setUsage(usage).setSamples(vk::SampleCountFlagBits::e1).setSharingMode(vk::SharingMode::eExclusive);
        image = device.device.createImage(imageCreateInfo);

        vk::MemoryRequirements memRequirements = device.device.getImageMemoryRequirements(image);
        vk::MemoryAllocateInfo allocInfo {};
        allocInfo.setAllocationSize(memRequirements.size)
                 .setMemoryTypeIndex(physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties));
        imageMemory = device.device.allocateMemory(allocInfo);
        device.device.bindImageMemory(image, imageMemory, 0);
    }

    std::vector<vk::ImageView> AZSwapChain::createImageViews(vk::Device device, std::vector<vk::Image>& swapChainImages, vk::Format format)
    {
        std::vector<vk::ImageView> swapChainImageViews;
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            swapChainImageViews[i] = createImageView(swapChainImages[i], format,  vk::ImageAspectFlagBits::eColor);
        }
        return swapChainImageViews;
    }

    vk::SurfaceFormatKHR AZSwapChain::chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == vk::Format {VK_FORMAT_B8G8R8A8_SRGB} && availableFormat.colorSpace == vk::ColorSpaceKHR {VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
            {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    vk::PresentModeKHR AZSwapChain::choosePresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox)
            {
                return availablePresentMode;
            }
        }
        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D AZSwapChain::chooseExtent(GLFWwindow* window, const vk::SurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);

        vk::Extent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void AZSwapChain::initSwapChainFramebuffers(AZRenderPass& renderPass)
    {
        vk::Format depthFormat = vk::Format::eD32Sfloat;
        createImage(swapChainExtent.width, swapChainExtent.height, depthFormat, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eDepthStencilAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, depthImage, depthImageMemory);
        depthImageView = createImageView(depthImage, depthFormat, vk::ImageAspectFlagBits::eDepth);
        
        swapChainFramebuffers.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            uint32_t width = swapChainExtent.width;
            uint32_t height = swapChainExtent.height;
            auto& imageView = swapChainImageViews[i];
            AZFramebufferDesc fboDesc{ {imageView, depthImageView}, renderPass.renderPass, width, height };
            swapChainFramebuffers[i] = AZFramebuffer(device, fboDesc);
        }
    }
}