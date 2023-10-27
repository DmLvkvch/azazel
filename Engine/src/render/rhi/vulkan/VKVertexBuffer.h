#pragma once

#include "render/VertexBuffer.h"
#include "vk_headers.h"

namespace Azazel
{
    class VKVertexBuffer : public VertexBuffer
    {
    public:
        VKVertexBuffer(VkDevice & device, VkPhysicalDevice & physicalDevice, const void* data, size_t size);
        ~VKVertexBuffer();
        void bind() const override;
        void unbind() const override;
        void setLayout(const BufferLayout& bufferlayout) override;
        void updateSubData(int offset, void* data, int size) override;
        const BufferLayout& getBufferLayout() const override;
    
    private:
        void createVertexBuffer(const void* vertices, uint64_t size);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    private:
        unsigned int rendererID;
        BufferLayout bufferLayout;
        VkDevice& device;
        VkPhysicalDevice& physicalDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
    };
}