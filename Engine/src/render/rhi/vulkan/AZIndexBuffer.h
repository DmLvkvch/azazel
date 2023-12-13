#pragma once

#include "render/IndexBuffer.h"
#include "vk_headers.h"

namespace Azazel
{
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
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        unsigned int count;

        VkCommandPool commandPool;
        VkQueue graphicsQueue;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
    };
}