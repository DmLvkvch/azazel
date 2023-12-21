#pragma once

#include "vk_headers.h"

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
                       VkPhysicalDevice physicalDevice, 
                       VkCommandPool commandPool, 
                       VkQueue graphicsQueue,
                       BufferDesc bufferDesc);

        ~AZVertexBuffer();
    
    private:
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createVertexBuffer(const void* vertices, uint64_t size);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void destroy();

    public:
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
    };

    class AZIndexBuffer
    {
    public:
        AZIndexBuffer()
        {
        }
        
        AZIndexBuffer(VkDevice device, 
                      VkPhysicalDevice physicalDevice, 
                      VkCommandPool commandPool, 
                      VkQueue graphicsQueue, 
                      const void* indices, 
                      size_t indicesCount);

        ~AZIndexBuffer();

        void destroy();

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createIndexBuffer(const void* indices, uint64_t size);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer,          VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        size_t count;

        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
    };
}
