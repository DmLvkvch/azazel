#pragma once


#include <cstdint>
#include <cstddef>

#include "vk_headers.h"

struct VmaAllocator_T;
struct VmaAllocation_T;
using VmaAllocator = VmaAllocator_T*;
using VmaAllocation = VmaAllocation_T*;

namespace Azazel
{

    enum class MemoryUsage
    {
        GPU_ONLY = 0,
        CPU_ONLY,
        CPU_TO_GPU,
        GPU_TO_CPU,
        CPU_COPY,
        GPU_LAZILY_ALLOCATED
    };

    VmaAllocator getVulkanAllocator();
    void deallocateImage(const VkImage& image, VmaAllocation allocation);
    void deallocateBuffer(const VkBuffer& buffer, VmaAllocation allocation);
    VmaAllocation allocateImage(const VkImageCreateInfo& imageCreateInfo, MemoryUsage usage, VkImage* image);
    VmaAllocation allocateBuffer(const VkBufferCreateInfo& bufferCreateInfo, MemoryUsage usage, VkBuffer* buffer);
    uint8_t* mapMemory(VmaAllocation allocation);
    void unmapMemory(VmaAllocation allocation);
    void flushMemory(VmaAllocation allocation, size_t byteSize, size_t offset);
}