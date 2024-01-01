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

        void createBuffer(VkDevice device, 
                          PhysicalDevice& physicalDevice,
                          VkDeviceSize size, 
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties, 
                          VkBuffer& buffer, 
                          VkDeviceMemory& uniformBufferMemory);

        void updateData(const void* data, VkDeviceSize size);

        void map(VkDeviceSize size);

        void unmap();

        void destroy();

        ~AZUniformBuffer()
        {

        }

        VkDevice device;
        void* hostVisibleData = nullptr;
        VkBuffer uniformBuffer;
        VkDeviceMemory uniformBufferMemory;
    };
}
