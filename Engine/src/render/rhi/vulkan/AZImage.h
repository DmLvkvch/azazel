#pragma once

#include "vk_headers.h"
#include "AZContext.h"
#include <stb_image/stb_image.h>
#include "render/TextureData.h"

namespace Azazel
{
    class AZImage
    {
    public:
        AZImage(TextureData textureData, VkFormat format) 
        {
            createTextureImage(textureData.width, textureData.height, textureData.data, format);
        }

        ~AZImage() 
        {
            destroy();
        }

        void destroy();
    
        void createTextureImage(int width, int height, unsigned char* pixels, VkFormat format);
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
    };

    class AZTextureSampler
    {
    public:
        AZTextureSampler() : sampler(VK_NULL_HANDLE) {}

        AZTextureSampler(VkFilter filter, VkSamplerAddressMode mode)
        {
            auto& physicalDevice = getVulkanContext().getPhysicalDevice();
            auto& device = getVulkanContext().getVulkanDevice();

            VkSamplerCreateInfo samplerInfo{};
            samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerInfo.magFilter = filter;
            samplerInfo.minFilter = filter;
            samplerInfo.addressModeU = mode;
            samplerInfo.addressModeV = mode;
            samplerInfo.addressModeW = mode;
            samplerInfo.anisotropyEnable = physicalDevice.getPhysicalDeviceFeatures().samplerAnisotropy;
            samplerInfo.maxAnisotropy = physicalDevice.getPhysicalDeviceProperties().limits.maxSamplerAnisotropy;
            samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
            samplerInfo.unnormalizedCoordinates = VK_FALSE;
            samplerInfo.compareEnable = VK_FALSE;
            samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

            vkCreateSampler(device.device, &samplerInfo, nullptr, &sampler);
        }

        ~AZTextureSampler()
        {
            destroy();
        }

        void destroy();

        VkSampler sampler;
    };
    
    class AZImageView
    {
    public:
        AZImageView(AZImage& image, VkFormat format, VkImageAspectFlags aspectFlags)
        {
            this->imageView = createImageView(getVulkanContext().getVulkanDevice(), image.textureImage, format, aspectFlags);
        }

        ~AZImageView()
        {
            destroy();
        }

        void destroy();

        VkImageView createImageView(const VulkanDevice& device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
        {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = image;
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = format;
            viewInfo.subresourceRange.aspectMask = aspectFlags;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            VkImageView imageView;
            vkCreateImageView(device.device, &viewInfo, nullptr, &imageView);
            return imageView;
        }

        VkImageView imageView;
    };
}
