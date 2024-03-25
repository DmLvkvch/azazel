#define VMA_IMPLEMENTATION

#include <vk_mem_alloc.h>
#include "VulkanMemoryAllocator.h"
#include "AZContext.h"

namespace Azazel
{
    VmaMemoryUsage memoryUsageToNative(MemoryUsage usage)
    {
        constexpr VmaMemoryUsage mappingTable[] =
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

    void deallocateImage(const VkImage& image, VmaAllocation allocation)
    {
        vmaDestroyImage(getVulkanAllocator(), image, allocation);
    }

    void deallocateBuffer(const VkBuffer& buffer, VmaAllocation allocation)
    {
        vmaDestroyBuffer(getVulkanAllocator(), buffer, allocation);
    }

    VmaAllocation allocateImage(const VkImageCreateInfo& imageCreateInfo, MemoryUsage usage, VkImage* image)
    {
        VmaAllocation allocation = { };
        VmaAllocationCreateInfo allocationInfo = { };
        allocationInfo.usage = memoryUsageToNative(usage);
        (void)vmaCreateImage(getVulkanAllocator(), (VkImageCreateInfo*)&imageCreateInfo, &allocationInfo, (VkImage*)image, &allocation, nullptr);
        return allocation;
    }

    VmaAllocation allocateBuffer(const VkBufferCreateInfo& bufferCreateInfo, MemoryUsage usage, VkBuffer* buffer)
    {
        VmaAllocation allocation = { };
        VmaAllocationCreateInfo allocationInfo = { };
        allocationInfo.usage = memoryUsageToNative(usage);
        (void)vmaCreateBuffer(getVulkanAllocator(), (VkBufferCreateInfo*)&bufferCreateInfo, &allocationInfo, (VkBuffer*)buffer, &allocation, nullptr);
        return allocation;
    }

    uint8_t* mapMemory(VmaAllocation allocation)
    {
        void* memory = nullptr;
        vmaMapMemory(getVulkanAllocator(), allocation, &memory);
        return (uint8_t*)memory;
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