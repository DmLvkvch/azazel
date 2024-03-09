#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class VulkanDevice;
    class AZCommandBuffer;

    class AZCommandPool
    {
    public:
        AZCommandPool()
        {

        }

        AZCommandPool(VkDevice device, int queueIndex);

        ~AZCommandPool()
        {

        }

        AZCommandBuffer* allocateCommandBuffer(VkDevice device);

        void reset();

        void destroy();

    public:
        VkDevice device;
        VkCommandPool commandPool;
    };

    class AZCommandBuffer
    {
    public:
        AZCommandBuffer();

        AZCommandBuffer(VkDevice device, VkCommandPool commandPool);

        ~AZCommandBuffer();

        void begin();

        void end();

        void reset();

        void* getAPIBuffer();

        static VkCommandBuffer beginSingleTimeCommands(VulkanDevice& device, AZCommandPool& commandPool);

        static void endSingleTimeCommands(VulkanDevice& device, AZCommandPool& commandPool, VkCommandBuffer commandBuffer);

    public:
        VkCommandBuffer commandBuffer;
    };
}