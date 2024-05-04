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
        AZBuffer(const BufferDesc& bufferDesc);
        ~AZBuffer();
        void destroy();
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
        void copy(const AZBuffer& dstBuffer);
        void copyData(const void* data, size_t sz);
        void map();
        void unmap();

        void* hostVisibleData = nullptr;
        vk::Buffer buffer;
        VkDeviceSize size = 0;
        VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
    };

    class AZVertexBuffer
    {
    public:
        AZVertexBuffer(const BufferDesc& bufferDesc);
    public:
        AZBuffer buffer;
    };

    class AZIndexBuffer
    {
    public:
        AZIndexBuffer(const BufferDesc& bufferDesc);
    public:
        AZBuffer buffer;
        size_t indicesCount;
    };

    class AZUniformBuffer
    {
    public:
        AZUniformBuffer(const BufferDesc& bufferDesc);
        ~AZUniformBuffer();
        void updateData(const void* data, VkDeviceSize size);
    public:
        AZBuffer buffer;
    };
}
