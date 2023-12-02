#pragma once

#include "render/VertexBuffer.h"
#include "vk_headers.h"

namespace Azazel
{
    class VKVertexBuffer
    {
    public:
        VKVertexBuffer(VkDevice device, 
                       VkPhysicalDevice physicalDevice, 
                       VkCommandPool commandPool, 
                       VkQueue graphicsQueue, 
                       const void* data, 
                       size_t size);
        ~VKVertexBuffer();
    
    private:
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createVertexBuffer(const void* vertices, uint64_t size);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    
    public:
        unsigned int rendererID;
        BufferLayout bufferLayout;
        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
    };
}