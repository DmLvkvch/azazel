#pragma once

#include "vk_headers.h"
#include "AZDevice.h"

namespace Azazel
{
    enum BufferType
    {
        INDEX_BUFFER,
        VERTEX_BUFFER,
        UNIFORM_BUFFER
    };
    
    struct BufferDesc
    {
        const void* data;
        uint64_t size;
        VkBufferUsageFlags bufferUsageFlags;
        VkMemoryPropertyFlags memoryPropertyFlags;
    };

    class AZBuffer
    {
    public:
        AZBuffer()
        {

        }

        AZBuffer(const BufferDesc& bufferDesc);

        ~AZBuffer()
        {
            destroy();
        }

        void destroy();

        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

        void copy(const AZBuffer& dstBuffer);

        void map();

        void unmap();

        void* hostVisibleData = nullptr;
        VkDeviceSize size = 0;
        VkBuffer buffer = VK_NULL_HANDLE;
        VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
    };

    class AZStageBuffer
    {
    public:
        AZStageBuffer(const VulkanDevice& device, 
                      const PhysicalDevice& physicalDevice, 
                      VkDeviceSize size, 
                      const void* bufferData)
        {
            createBuffer(device, physicalDevice, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

            void* data;
            vkMapMemory(device.device, stagingBufferMemory, 0, size, 0, &data);
            memcpy(data, bufferData, static_cast<size_t>(size));
            vkUnmapMemory(device.device, stagingBufferMemory);
        }

        void createBuffer(const VulkanDevice& device, 
                          const PhysicalDevice& physicalDevice,
                          VkDeviceSize size,
                          VkBufferUsageFlags usage, 
                          VkMemoryPropertyFlags properties)
        {
            VkBufferCreateInfo bufferInfo{};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = size;
            bufferInfo.usage = usage;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            vkCreateBuffer(device.device, &bufferInfo, nullptr, &stagingBuffer);

            VkMemoryRequirements memRequirements = device.getMemoryRequirements(stagingBuffer);

            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memRequirements.size;
            allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

            vkAllocateMemory(device.device, &allocInfo, nullptr, &stagingBufferMemory);

            vkBindBufferMemory(device.device, stagingBuffer, stagingBufferMemory, 0);
        }

        ~AZStageBuffer()
        {

        }

        void destroy()
        {
            // vkDestroyBuffer(device.device, stagingBuffer, nullptr);
            // vkFreeMemory(device.device, stagingBufferMemory, nullptr);
        }
    private:
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
    };

    class AZVertexBuffer
    {
    public:
        AZVertexBuffer(BufferDesc bufferDesc);

    public:
        AZBuffer buffer;
    };

    class AZIndexBuffer
    {
    public:
        AZIndexBuffer(const VulkanDevice& device, 
                      const PhysicalDevice& physicalDevice, 
                      const void* indices,
                      size_t indicesCount);

        ~AZIndexBuffer();

        void destroy();
        void createIndexBuffer(const PhysicalDevice& physicalDevice, const void* indices, uint64_t size);
        void createBuffer(const PhysicalDevice& physicalDevice, 
                          VkDeviceSize size, VkBufferUsageFlags usage, 
                          VkMemoryPropertyFlags properties, 
                          VkBuffer& buffer, 
                          VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void map(VkDeviceSize size);
        void unmap();

        const VulkanDevice& device;
        VkBuffer buffer;
        VkDeviceMemory bufferMemory;
        void* hostVisibleData = nullptr;
    };

    class AZUniformBuffer
    {
    public:
        AZUniformBuffer(const VulkanDevice& device, 
                        const PhysicalDevice& physicalDevice, 
                        VkDeviceSize size, 
                        const void* data);
        void destroy();
        ~AZUniformBuffer();
        void createBuffer(const VulkanDevice& device, 
                          const PhysicalDevice& physicalDevice,
                          VkDeviceSize size, 
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties, 
                          VkBuffer& buffer, 
                          VkDeviceMemory& uniformBufferMemory);
        void updateData(const void* data, VkDeviceSize size);
        void map(VkDeviceSize size);
        void unmap();
    public:
        const VulkanDevice& device;
        VkBuffer buffer;
        VkDeviceMemory bufferMemory;
        void* hostVisibleData = nullptr;
    };
}
