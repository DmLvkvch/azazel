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

    void AZBuffer::copy(const AZBuffer& dstBuffer)
    {
        auto& device = getVulkanContext().getVulkanDevice();
        auto& commandPool = getVulkanContext().getCommandPool();
        auto commandBuffer = AZCommandBuffer::beginSingleTimeCommands(device, commandPool);
        VkBufferCopy copyRegion {};
        copyRegion.size = size;
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

    AZVertexBuffer::AZVertexBuffer(BufferDesc bufferDesc)
    : buffer(bufferDesc)
    {
        BufferDesc stageBufferDesc {nullptr, bufferDesc.size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};
        AZBuffer stageBuffer {stageBufferDesc};
        stageBuffer.map();
        memcpy(stageBuffer.hostVisibleData, bufferDesc.data, (size_t) bufferDesc.size);
        stageBuffer.unmap();
        stageBuffer.copy(buffer);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    AZIndexBuffer::AZIndexBuffer(const VulkanDevice& device,
                                 const PhysicalDevice& physicalDevice,
                                 const void* indices, 
                                 size_t indicesCount)
    : device(device)
    {
        createIndexBuffer(physicalDevice, indices, sizeof(unsigned int) * indicesCount);
    }

    AZIndexBuffer::~AZIndexBuffer()
    {
        destroy();
    }

    void AZIndexBuffer::destroy()
    {

    }
    
    void AZIndexBuffer::createIndexBuffer(const PhysicalDevice& physicalDevice, const void* indices, uint64_t size)
    {
        VkDeviceSize bufferSize = size;
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device.device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices, (size_t) bufferSize);
        vkUnmapMemory(device.device, stagingBufferMemory);

        createBuffer(physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, bufferMemory);

        copyBuffer(stagingBuffer, buffer, bufferSize);

        vkDestroyBuffer(device.device, stagingBuffer, nullptr);
        vkFreeMemory(device.device, stagingBufferMemory, nullptr);
    }

    void AZIndexBuffer::createBuffer(const PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
    {
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
        allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

        vkAllocateMemory(device.device, &allocInfo, nullptr, &bufferMemory);
        vkBindBufferMemory(device.device, buffer, bufferMemory, 0);
    }

    void AZIndexBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
    {
        auto& commandPool = getVulkanContext().getCommandPool();

        auto commandBuffer = AZCommandBuffer::beginSingleTimeCommands(device, commandPool);
        VkBufferCopy copyRegion {};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
        AZCommandBuffer::endSingleTimeCommands(device, commandPool, commandBuffer);
    }

    void AZIndexBuffer::map(VkDeviceSize size)
    {
        vkMapMemory(device.device, bufferMemory, 0, size, 0, &hostVisibleData);
    }

    void AZIndexBuffer::unmap()
    {
        vkUnmapMemory(device.device, bufferMemory);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    AZUniformBuffer::AZUniformBuffer(const VulkanDevice& device, 
                                     const PhysicalDevice& physicalDevice, 
                                     VkDeviceSize size, 
                                     const void* data)
    : device(device)
    {
        VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        VkBufferUsageFlagBits bufferUsageFlagBits = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        createBuffer(device, physicalDevice, size, bufferUsageFlagBits, memoryPropertyFlags, buffer, bufferMemory);
    }

    AZUniformBuffer::~AZUniformBuffer()
    {
        destroy();
    }

    void AZUniformBuffer::destroy()
    {

    }

    void AZUniformBuffer::createBuffer(const VulkanDevice& device, const PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& uniformBufferMemory)
    {
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
        allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

        vkAllocateMemory(device.device, &allocInfo, nullptr, &bufferMemory);

        vkBindBufferMemory(device.device, buffer, bufferMemory, 0);

        map(size);
    }
    
    void AZUniformBuffer::updateData(const void* data, VkDeviceSize size)
    {
        memcpy(hostVisibleData, data, size);
    }
    
    void AZUniformBuffer::map(VkDeviceSize size)
    {
        vkMapMemory(device.device, bufferMemory, 0, size, 0, &hostVisibleData);
    }

    void AZUniformBuffer::unmap()
    {
        vkUnmapMemory(device.device, bufferMemory);
    }
}