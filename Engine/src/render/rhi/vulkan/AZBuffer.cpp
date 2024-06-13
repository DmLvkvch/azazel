#include "AZBuffer.h"
#include "AZContext.h"
#include "VulkanMemoryAllocator.h"

namespace Azazel
{
    AZBuffer::AZBuffer(const BufferDesc& bufferDesc)
    : size(bufferDesc.size), bufferMemory(VK_NULL_HANDLE), buffer(VK_NULL_HANDLE)
    {
        createBuffer(bufferDesc.size, bufferDesc.bufferUsageFlags, bufferDesc.memoryPropertyFlags);
    }

    AZBuffer::~AZBuffer()
    {
        destroy();
    }
    
    void AZBuffer::createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties)
    {
        auto& device = getVulkanContext().getVulkanDevice();
        
        vk::BufferCreateInfo bufferCreateInfo;
        bufferCreateInfo.setSize(size).setUsage(usage).setSharingMode(vk::SharingMode::eExclusive);
        buffer = device.device.createBuffer(bufferCreateInfo);
        
        vk::MemoryRequirements memRequirements = device.getMemoryRequirements(buffer);
        vk::MemoryAllocateInfo allocateInfo {};
        allocateInfo.setAllocationSize(memRequirements.size).setMemoryTypeIndex(device.physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties));
        bufferMemory = device.device.allocateMemory(allocateInfo);
        device.device.bindBufferMemory(buffer, bufferMemory, 0);
    }

    void AZBuffer::copyData(const void* data, size_t sz)
    {
        map();
        memcpy(hostVisibleData, data, sz);
        unmap();
    }

    void AZBuffer::copy(const AZBuffer& dstBuffer)
    {
        auto& device = getVulkanContext().getVulkanDevice();
        auto& commandPool = getVulkanContext().getCommandPool();
        auto commandBuffer = AZCommandBuffer::beginSingleTimeCommands(device, commandPool);
        vk::BufferCopy copyRegion {0, 0, size};
        vk::ArrayProxy<vk::BufferCopy> bufferCopies {copyRegion};
        commandBuffer.copyBuffer(buffer, dstBuffer.buffer, bufferCopies);
        AZCommandBuffer::endSingleTimeCommands(device, commandPool, commandBuffer);
    }

    void AZBuffer::map()
    {
        auto& device = getVulkanContext().getVulkanDevice();
        vkMapMemory(device.device, bufferMemory, 0, size, 0, &hostVisibleData);
    }

    void AZBuffer::unmap()
    {
        auto& device = getVulkanContext().getVulkanDevice();
        vkUnmapMemory(device.device, bufferMemory);
        hostVisibleData = nullptr;
    }

    void AZBuffer::destroy()
    {
        auto& device = getVulkanContext().getVulkanDevice();
        if (buffer)
        {
            vkDestroyBuffer(device.device, buffer, nullptr);
        }
        if (bufferMemory)
        {
            vkFreeMemory(device.device, bufferMemory, nullptr);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZVertexBuffer::AZVertexBuffer(const BufferDesc& bufferDesc)
    : buffer(bufferDesc)
    {
        BufferDesc stageBufferDesc {nullptr, bufferDesc.size, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent };
        AZBuffer stageBuffer {stageBufferDesc};
        stageBuffer.copyData(bufferDesc.data, bufferDesc.size);
        stageBuffer.copy(buffer);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZIndexBuffer::AZIndexBuffer(const BufferDesc& bufferDesc)
    : buffer(bufferDesc), indicesCount(bufferDesc.size / sizeof(uint32_t))
    {
        BufferDesc stageBufferDesc {nullptr, bufferDesc.size, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent};
        AZBuffer stageBuffer {stageBufferDesc};
        stageBuffer.copyData(bufferDesc.data, bufferDesc.size);
        stageBuffer.copy(buffer);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    AZUniformBuffer::AZUniformBuffer(const BufferDesc& bufferDesc)
    : buffer(bufferDesc)
    {
        buffer.map();
    }

    AZUniformBuffer::~AZUniformBuffer()
    {
    }
    
    void AZUniformBuffer::updateData(const void* data, VkDeviceSize size)
    {
        memcpy(buffer.hostVisibleData, data, size);
    }
}