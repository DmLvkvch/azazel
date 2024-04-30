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

        AZCommandBuffer* allocateCommandBuffer(const VulkanDevice& device);

        void reset();

        void destroy();

    public:
        const VulkanDevice& device;
        VkCommandPool commandPool;
    };

    class AZCommandBuffer
    {
    public:
        AZCommandBuffer();

        AZCommandBuffer(const VulkanDevice& device, const AZCommandPool& commandPool);

        ~AZCommandBuffer();

        void begin() const;

        void end() const;

        void reset() const;

        void* getAPIBuffer();

        static VkCommandBuffer beginSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool);

        static void endSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool, const VkCommandBuffer commandBuffer);

    public:
        VkCommandBuffer commandBuffer;
    };
}