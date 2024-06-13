#include "AZImage.h"
#include "AZBuffer.h"

namespace Azazel
{
    void AZImage::createTextureImage(int width, int height, unsigned char* pixels, vk::Format format)
    {
        uint64_t pixelSize = 4;
        VkDeviceSize imageSize = pixelSize * width * height;
        auto& ctx = getVulkanContext();
        auto& device = ctx.getVulkanDevice();
        BufferDesc stageBufferDesc {pixels, imageSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent};
        AZBuffer stageBuffer {stageBufferDesc};
        stageBuffer.copyData(pixels, imageSize);
        createImage(width, height, format, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled, vk::MemoryPropertyFlagBits::eDeviceLocal, textureImage, textureImageMemory);
        transitionImageLayout(textureImage, format, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);
        copyBufferToImage(stageBuffer.buffer, textureImage, static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        transitionImageLayout(textureImage, format, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal);
    }

    void AZImage::createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory imageMemory)
    {
        auto& ctx = getVulkanContext();
        auto& device = ctx.getVulkanDevice();
        auto& physicalDevice = device.physicalDevice;
        vk::ImageCreateInfo imageInfo {};
        imageInfo.imageType = vk::ImageType::e2D;
        vk::Extent3D extent {width, height, 1};
        imageInfo.setExtent(extent);
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = vk::ImageLayout::eUndefined;
        imageInfo.usage = usage;
        imageInfo.samples = vk::SampleCountFlagBits::e1;
        imageInfo.sharingMode = vk::SharingMode::eExclusive;
        image = device.device.createImage(imageInfo);
        
        auto memRequirements = device.device.getImageMemoryRequirements(image);
        vk::MemoryAllocateInfo allocInfo {};
        allocInfo.setAllocationSize(memRequirements.size).setMemoryTypeIndex(physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties));
        imageMemory = device.device.allocateMemory(allocInfo);
        device.device.bindImageMemory(image, imageMemory, 0);
    }

    void AZImage::transitionImageLayout(vk::Image image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout)
    {
        auto& ctx = getVulkanContext();
        auto& device = ctx.getVulkanDevice();
        auto& commandPool = ctx.getCommandPool();
        vk::CommandBuffer commandBuffer = AZCommandBuffer::beginSingleTimeCommands(device, commandPool);
        vk::ImageMemoryBarrier barrier{};
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;
        vk::PipelineStageFlags sourceStage {};
        vk::PipelineStageFlags destinationStage {};
        if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal)
        {
            barrier.srcAccessMask = vk::AccessFlagBits::eNone;
            barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
            sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
            destinationStage = vk::PipelineStageFlagBits::eTransfer;
        }
        else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal)
        {
            barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
            barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;
            sourceStage = vk::PipelineStageFlagBits::eTransfer;
            destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
        }
        vk::ArrayProxy<vk::ImageMemoryBarrier> barriers {1, &barrier};
        commandBuffer.pipelineBarrier(sourceStage, destinationStage, vk::DependencyFlagBits::eByRegion, {}, {}, barriers);
        AZCommandBuffer::endSingleTimeCommands(device, commandPool, commandBuffer);
    }
    void AZImage::copyBufferToImage(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height) 
    {
        auto& ctx = getVulkanContext();
        auto& device = ctx.getVulkanDevice();
        auto& commandPool = ctx.getCommandPool();
        vk::CommandBuffer commandBuffer = AZCommandBuffer::beginSingleTimeCommands(device, commandPool);
        vk::ImageSubresourceLayers imageSubresourceLayers {};
        imageSubresourceLayers.setAspectMask(vk::ImageAspectFlagBits::eColor).setMipLevel(0).setLayerCount(1).setBaseArrayLayer(0);
        vk::BufferImageCopy region {};
         region.setBufferOffset(0).setBufferRowLength(0).setBufferImageHeight(0)
              .setImageSubresource(imageSubresourceLayers).setImageOffset({0, 0, 0}).setImageExtent({width, height, 1});
        vk::ArrayProxy<vk::BufferImageCopy> regions { region };
        commandBuffer.copyBufferToImage(buffer, image, vk::ImageLayout::eTransferDstOptimal, regions);
        AZCommandBuffer::endSingleTimeCommands(device, commandPool, commandBuffer);
    }
    void AZImage::destroy()
    {
        auto& device = getVulkanContext().getVulkanDevice();
        device.device.waitIdle();
        device.device.destroyImage(textureImage);
        device.device.freeMemory(textureImageMemory);
    }

    void AZTextureSampler::destroy()
    {
        
    }

    void AZImageView::destroy()
    {

    }
    
}