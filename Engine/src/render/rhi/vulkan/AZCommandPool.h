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

        AZCommandPool(VkDevice device, int queueIndex)
        {
            VkCommandPoolCreateInfo poolInfo {};
            {
                poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                poolInfo.queueFamilyIndex = queueIndex;
            }
            vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
        }

        void reset()
        {

        }

    public:
        VkCommandPool commandPool;
    };
}