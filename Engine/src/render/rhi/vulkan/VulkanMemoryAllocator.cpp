#define VMA_IMPLEMENTATION

#include <vk_mem_alloc.h>
#include "VulkanMemoryAllocator.h"
#include "AZContext.h"

namespace Azazel
{
    VmaMemoryUsage memoryUsageToNative(MemoryUsage usage)
    {
        static VmaMemoryUsage mappingTable[] =
        {
            VMA_MEMORY_USAGE_GPU_ONLY,
            VMA_MEMORY_USAGE_CPU_ONLY,
            VMA_MEMORY_USAGE_CPU_TO_GPU,
            VMA_MEMORY_USAGE_GPU_TO_CPU,
            VMA_MEMORY_USAGE_CPU_COPY,
            VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED,
        };
        return mappingTable[(size_t)usage];
    }

    VmaAllocator getVulkanAllocator()
    {
        return getVulkanContext().getAllocator();
    }

    void deallocateImage(const vk::Image& image, VmaAllocation allocation)
    {
        vmaDestroyImage(getVulkanAllocator(), image, allocation);
    }

    void deallocateBuffer(const vk::Buffer& buffer, VmaAllocation allocation)
    {
        vmaDestroyBuffer(getVulkanAllocator(), buffer, allocation);
    }

    VmaAllocation allocateImage(const vk::ImageCreateInfo& imageCreateInfo, MemoryUsage usage, vk::Image* image)
    {
        VmaAllocation allocation = { };
        VmaAllocationCreateInfo allocationInfo = { };
        allocationInfo.usage = memoryUsageToNative(usage);
        (void)vmaCreateImage(getVulkanAllocator(), (VkImageCreateInfo*)&imageCreateInfo, &allocationInfo, (VkImage*)image, &allocation, nullptr);
        return allocation;
    }

    VmaAllocation allocateBuffer(const vk::BufferCreateInfo& bufferCreateInfo, MemoryUsage usage, vk::Buffer* buffer)
    {
        VmaAllocation allocation = { };
        VmaAllocationCreateInfo allocationInfo = { };
        allocationInfo.usage = memoryUsageToNative(usage);
        (void)vmaCreateBuffer(getVulkanAllocator(), (VkBufferCreateInfo*)&bufferCreateInfo, &allocationInfo, (VkBuffer*)buffer, &allocation, nullptr);
        return allocation;
    }

    void* mapMemory(VmaAllocation allocation)
    {
        void* memory = nullptr;
        vmaMapMemory(getVulkanAllocator(), allocation, &memory);
        return (uint8_t*) memory;
    }

    void unmapMemory(VmaAllocation allocation)
    {
        vmaUnmapMemory(getVulkanAllocator(), allocation);
    }

    void flushMemory(VmaAllocation allocation, size_t byteSize, size_t offset)
    {
        vmaFlushAllocation(getVulkanAllocator(), allocation, offset, byteSize);
    }
}