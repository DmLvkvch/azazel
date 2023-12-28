#pragma once

#include "vk_headers.h"

namespace Azazel
{

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

    public:
        VkCommandBuffer commandBuffer;
    };
}