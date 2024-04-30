#include "AZBuffer.h"
#include "AZContext.h"

namespace Azazel
{
    AZBuffer::AZBuffer(const BufferDesc& bufferDesc)
    : size(bufferDesc.size), bufferMemory(VK_NULL_HANDLE), buffer(VK_NULL_HANDLE)
    {
        createBuffer(bufferDesc.size, bufferDesc.bufferUsageFlags, bufferDesc.memoryPropertyFlags);
    }
    
    void AZBuffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
    {
        auto& device = getVulkanContext().getVulkanDevice();
        
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        vkCreateBuffer(device.device, &bufferInfo, nullptr, &buffer);
        VkMemoryRequirements memRequirements = device.getMemoryRequirements(buffer);
        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = getVulkanContext().getPhysicalDevice().findMemoryType(memRequirements.memoryTypeBits, properties);
        vkAllocateMemory(device.device, &allocInfo, nullptr, &bufferMemory);
        vkBindBufferMemory(device.device, buffer, bufferMemory, 0);
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
        VkBufferCopy copyRegion {0, 0, size};
        vkCmdCopyBuffer(commandBuffer, buffer, dstBuffer.buffer, 1, &copyRegion);
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

    AZVertexBuffer::AZVertexBuffer(const BufferDesc& bufferDesc)
    : buffer(bufferDesc)
    {
        BufferDesc stageBufferDesc {nullptr, bufferDesc.size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};
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
        BufferDesc stageBufferDesc {nullptr, bufferDesc.size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};
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