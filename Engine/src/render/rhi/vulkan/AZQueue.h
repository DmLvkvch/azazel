#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZQueue
    {
    public:
        AZQueue()
        {

        }

        AZQueue(VkDevice device, uint32_t queueFamilyIndex);

        ~AZQueue()
        {

        }

        VkQueue createQueue(VkDevice device, uint32_t queueFamilyIndex);

        VkQueue get()
        {
            return queue;
        }

        VkQueue queue;
        VkQueueFlags flags;
        uint32_t queueFamilyIndex;
        uint32_t queueIndex;
    };
}