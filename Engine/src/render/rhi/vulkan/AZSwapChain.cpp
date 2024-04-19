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

    VkSwapchainKHR AZSwapChain::createSwapChain(GLFWwindow* window, AZSurface& surface)
    {
        VkSwapchainKHR swapChain;
        SwapChainSupportDetails swapChainSupport = surface.querySwapChainSupport(physicalDevice.get());
        surfaceFormat   = chooseSwapSurfaceFormat(swapChainSupport.formats);
        presentMode     = chooseSwapPresentMode(swapChainSupport.presentModes);
        swapChainExtent = chooseSwapExtent(window, swapChainSupport.capabilities);

        imageCount = std::min(swapChainSupport.capabilities.maxImageCount, swapChainSupport.capabilities.minImageCount + 1);

        VkSwapchainCreateInfoKHR createInfo{};
        {
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = surface.surface;
            createInfo.minImageCount = imageCount;
            createInfo.imageFormat = surfaceFormat.format;
            createInfo.imageColorSpace = surfaceFormat.colorSpace;
            createInfo.imageExtent = swapChainExtent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        }

        auto& indices = physicalDevice.getQueueFamilyIndices();
        auto queueFamilyIndices = indices.getIndices();

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        vkCreateSwapchainKHR(device.device, &createInfo, nullptr, &swapChain);

        vkGetSwapchainImagesKHR(device.device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device.device, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        return swapChain;
    }

    VkImageView AZSwapChain::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = aspectFlags;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        VkImageView imageView;
        vkCreateImageView(device.device, &createInfo, nullptr, &imageView);
        return imageView;
    }

    std::vector<VkImageView> AZSwapChain::createImageViews(VkDevice device, std::vector<VkImage>& swapChainImages, VkFormat format)
    {
        std::vector<VkImageView> swapChainImageViews;
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            swapChainImageViews[i] = createImageView(swapChainImages[i], format, VK_IMAGE_ASPECT_COLOR_BIT);
        }
        return swapChainImageViews;
    }

    VkSurfaceFormatKHR AZSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }

    VkPresentModeKHR AZSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D AZSwapChain::chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void AZSwapChain::initSwapChainFramebuffers(AZRenderPass& renderPass)
    {
        VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;
        createImage(swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
        depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
        
        swapChainFramebuffers.resize(swapChainImageViews.size());
        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            uint32_t width = swapChainExtent.width;
            uint32_t height = swapChainExtent.height;
            auto& imageView = swapChainImageViews[i];
            AZFramebufferDesc fboDesc{ {imageView, depthImageView}, renderPass.renderPass, width, height };
            swapChainFramebuffers[i] = AZFramebuffer(device.device, fboDesc);
        }
    }
}