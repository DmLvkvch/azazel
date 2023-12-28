#pragma once

#include "vk_headers.h"
#include "AZDevice.h"

namespace Azazel
{
    enum BufferType
    {
        VERTEX
    };

    struct BufferDesc
    {
        const void* data;
        uint64_t size;
    };

    class AZVertexBuffer
    {
    public:
        AZVertexBuffer()
        {
        }
        
        AZVertexBuffer(VkDevice device,
                       PhysicalDevice& physicalDevice, 
                       VkCommandPool commandPool, 
                       VkQueue graphicsQueue,
                       BufferDesc bufferDesc);

        ~AZVertexBuffer();
    
    private:
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createVertexBuffer(PhysicalDevice& physicalDevice, const void* vertices, uint64_t size);
        void createBuffer(PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void map(VkDeviceSize size);
        void unmap();
        
        void destroy();

    public:
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkDevice device;
        void* hostVisibleData = nullptr;
    };

    class AZIndexBuffer
    {
    public:
        AZIndexBuffer()
        {
        }
        
        AZIndexBuffer(VkDevice device, 
                      PhysicalDevice& physicalDevice, 
                      VkCommandPool commandPool, 
                      VkQueue graphicsQueue, 
                      const void* indices, 
                      size_t indicesCount);

        ~AZIndexBuffer();

        void destroy();

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createIndexBuffer(PhysicalDevice& physicalDevice, const void* indices, uint64_t size);
        void createBuffer(PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        void map(VkDeviceSize size);
        void unmap();

        size_t count;

        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        void* hostVisibleData = nullptr;
    };

    class AZUniformBuffer
    {
    public:
        AZUniformBuffer()
        {

        }

        AZUniformBuffer(VkDevice device, 
                        PhysicalDevice& physicalDevice, 
                        VkDeviceSize size, 
                        const void* data)
        : device(device)
        {
            VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
            VkBufferUsageFlagBits bufferUsageFlagBits = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
            createBuffer(device, physicalDevice, size, bufferUsageFlagBits, memoryPropertyFlags, uniformBuffer, uniformBufferMemory);
        }

        void createBuffer(VkDevice device, PhysicalDevice& physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& uniformBufferMemory)
        {
            VkBufferCreateInfo bufferInfo{};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = size;
            bufferInfo.usage = usage;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);

            VkMemoryRequirements memRequirements;
            vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memRequirements.size;
            allocInfo.memoryTypeIndex = physicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

            vkAllocateMemory(device, &allocInfo, nullptr, &uniformBufferMemory);

            vkBindBufferMemory(device, buffer, uniformBufferMemory, 0);

            map(size);
        }

        void updateData(const void* data, VkDeviceSize size)
        {
            memcpy(hostVisibleData, data, size);
        }

        void map(VkDeviceSize size)
        {
            vkMapMemory(device, uniformBufferMemory, 0, size, 0, &hostVisibleData);
        }

        void unmap()
        {

        }

        ~AZUniformBuffer()
        {

        }

        VkDevice device;
        void* hostVisibleData = nullptr;
        VkBuffer uniformBuffer;
        VkDeviceMemory uniformBufferMemory;
    };
}
