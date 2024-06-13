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
    void deallocateImage(const vk::Image& image, VmaAllocation allocation);
    void deallocateBuffer(const vk::Buffer& buffer, VmaAllocation allocation);
    VmaAllocation allocateImage(const vk::ImageCreateInfo& imageCreateInfo, MemoryUsage usage, vk::Image* image);
    VmaAllocation allocateBuffer(const vk::BufferCreateInfo& bufferCreateInfo, MemoryUsage usage, vk::Buffer* buffer);
    void* mapMemory(VmaAllocation allocation);
    void unmapMemory(VmaAllocation allocation);
    void flushMemory(VmaAllocation allocation, size_t byteSize, size_t offset);
}