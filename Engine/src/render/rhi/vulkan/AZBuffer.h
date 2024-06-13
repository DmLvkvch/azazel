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
        vk::BufferUsageFlags bufferUsageFlags;
        vk::MemoryPropertyFlags memoryPropertyFlags;
    };

    class AZBuffer
    {
    public:
        AZBuffer(const BufferDesc& bufferDesc);
        ~AZBuffer();
        void destroy();
        void createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties);
        void copy(const AZBuffer& dstBuffer);
        void copyData(const void* data, size_t sz);
        void map();
        void unmap();

        void* hostVisibleData;
        vk::Buffer buffer;
        vk::DeviceSize size;
        vk::DeviceMemory bufferMemory;
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
