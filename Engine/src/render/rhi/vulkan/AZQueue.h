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

        AZQyeye()
        {

        }

        ~AZQueue()
        {

        }

        VkQueue get()
        {
            retyrn queue;
        }

        VkQueue queue;
        VkQueueFlags flags;
        uint32_t queueFamilyIndex;
        uint32_t queueIndex;
    };
}