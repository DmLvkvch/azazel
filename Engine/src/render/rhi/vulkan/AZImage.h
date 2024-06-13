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
        AZImage(TextureData textureData, vk::Format format)
        {
            createTextureImage(textureData.width, textureData.height, textureData.data, format);
        }

        ~AZImage() 
        {
            destroy();
        }

        void destroy();
    
        void createTextureImage(int width, int height, unsigned char* pixels, vk::Format format);
        void createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory imageMemory);
        void transitionImageLayout(vk::Image image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
        void copyBufferToImage(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height);

        vk::Image textureImage;
        vk::DeviceMemory textureImageMemory;
    };

    class AZTextureSampler
    {
    public:
        AZTextureSampler() : sampler(VK_NULL_HANDLE) {}

        AZTextureSampler(vk::Filter filter, vk::SamplerAddressMode mode)
        {
            auto& physicalDevice = getVulkanContext().getPhysicalDevice();
            auto& device = getVulkanContext().getVulkanDevice();

            vk::SamplerCreateInfo samplerCreateInfo {};
            samplerCreateInfo.setMagFilter(filter).setMinFilter(filter)
                             .setAddressModeU(mode).setAddressModeV(mode).setAddressModeW(mode)
                             .setAnisotropyEnable(physicalDevice.getPhysicalDeviceFeatures().samplerAnisotropy)
                             .setMaxAnisotropy(physicalDevice.getPhysicalDeviceProperties().limits.maxSamplerAnisotropy)
                             .setBorderColor(vk::BorderColor::eIntOpaqueBlack)
                             .setUnnormalizedCoordinates(VK_FALSE)
                             .setCompareEnable(VK_FALSE)
                             .setCompareOp(vk::CompareOp::eAlways)
                             .setMipmapMode(vk::SamplerMipmapMode::eLinear);

            sampler = device.device.createSampler(samplerCreateInfo);
        }

        ~AZTextureSampler()
        {
            destroy();
        }

        void destroy();

        vk::Sampler sampler;
    };
    
    class AZImageView
    {
    public:
        AZImageView(AZImage& image, vk::Format format, vk::ImageAspectFlags aspectFlags)
        {
            this->imageView = createImageView(getVulkanContext().getVulkanDevice(), image.textureImage, format, aspectFlags);
        }

        ~AZImageView()
        {
            destroy();
        }

        void destroy();

        vk::ImageView createImageView(const VulkanDevice& device, vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags)
        {
            vk::ImageViewCreateInfo imageViewCreateInfo {};
            vk::ImageSubresourceRange subResourceRange {};
            subResourceRange.setAspectMask(aspectFlags).setBaseMipLevel(0).setLevelCount(1).setBaseArrayLayer(0).setLayerCount(1);
            imageViewCreateInfo.setImage(image).setViewType(vk::ImageViewType::e2D)
                               .setFormat(format).setSubresourceRange(subResourceRange);
            return device.device.createImageView(imageViewCreateInfo);
        }

        VkImageView imageView;
    };
}
