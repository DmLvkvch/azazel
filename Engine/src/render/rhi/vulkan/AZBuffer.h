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
        void destroy();

    public:
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkDevice device;
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

        size_t count;

        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
    };

    class AZUniformBuffer
    {
    public:
        AZUniformBuffer()
        {

        }

        AZUniformBuffer(VkDeviceSize size)
        {
            
        }

        uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
        {
            VkPhysicalDeviceMemoryProperties memProperties;
            vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) 
                {
                    return i;
                }
            }

            throw std::runtime_error("failed to find suitable memory type!");
        }

        void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
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
            allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

            vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory);

            vkBindBufferMemory(device, buffer, bufferMemory, 0);
        }

        ~AZUniformBuffer()
        {

        }
    };
}
