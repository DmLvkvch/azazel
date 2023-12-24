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
}