#include "VKVertexBuffer.h"

namespace Azazel
{
    VKVertexBuffer::VKVertexBuffer(VkDevice & device, VkPhysicalDevice & physicalDevice, const void* data, size_t size)
    : device(device), physicalDevice(physicalDevice)
    {
        createVertexBuffer(data, size);
    }

    VKVertexBuffer::~VKVertexBuffer()
    {
    }

    void VKVertexBuffer::bind() const
    {
    }

    void VKVertexBuffer::unbind() const
    {
    }

    void VKVertexBuffer::updateSubData(int offset, void* data, int size)
    {
    }

    void VKVertexBuffer::setLayout(const BufferLayout& bufferLayout)
    {
         this->bufferLayout = bufferLayout;
    }

    const BufferLayout& VKVertexBuffer::getBufferLayout() const
    {
        return bufferLayout;
    }

    void VKVertexBuffer::createVertexBuffer(const void* vertices, uint64_t size)
    { 
        VkBufferCreateInfo bufferInfo {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

        void* data;
        vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
        memcpy(data, vertices, (size_t) bufferInfo.size);
        vkUnmapMemory(device, vertexBufferMemory);
    }

    uint32_t VKVertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) 
    {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

}