#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class VulkanDevice;
    class AZCommandBuffer;

    class AZCommandPool
    {
    public:
        AZCommandPool(const VulkanDevice& device, int queueIndex);
        ~AZCommandPool();

        vk::CommandBuffer allocateCommandBuffer(const VulkanDevice& device) const;
        void reset();
        void destroy();

    public:
        const VulkanDevice& device;
        vk::CommandPool commandPool;
    };

    class AZCommandBuffer
    {
    public:
        AZCommandBuffer();
        AZCommandBuffer(VkCommandBuffer commandBuffer);
        ~AZCommandBuffer();
        void begin() const;
        void end() const;
        void reset() const;
        void* getAPIBuffer();

        static vk::CommandBuffer beginSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool);
        static void endSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool, const vk::CommandBuffer& commandBuffer);
    public:
        vk::CommandBuffer commandBuffer;
    };
}