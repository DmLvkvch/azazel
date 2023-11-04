#pragma once

#include "render/IndexBuffer.h"
#include "vk_headers.h"

namespace Azazel
{
    class VKIndexBuffer : public IndexBuffer
    {
    public:
        VKIndexBuffer(VkDevice & device, 
                      VkPhysicalDevice & physicalDevice, 
                      VkCommandPool & commandPool, 
                      VkQueue & graphicsQueue, 
                      const void* indices, 
                      size_t indicesCount);

        ~VKIndexBuffer();

        void bind() const override;

        void unbind() const override;

        unsigned int getElementCount() const override;

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createIndexBuffer(const void* indices, uint64_t size);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    private:
        unsigned int rendererID;
        unsigned int count;

        VkCommandPool & commandPool;
        VkQueue & graphicsQueue;
        VkDevice& device;
        VkPhysicalDevice& physicalDevice;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
    };
}