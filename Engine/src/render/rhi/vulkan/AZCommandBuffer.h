#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class VKCommandBuffer
    {
    public:
        VKCommandBuffer(VkDevice device, VkCommandPool commandPool)
        {
            VkCommandBufferAllocateInfo allocInfo {};
            {
                allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.commandPool = commandPool;
                allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandBufferCount = 1;
            }
            vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
        }

        ~VKCommandBuffer()
        {

        }
    
        void begin()
        {

        }

        void end()
        {

        }
    public:
        VkCommandBuffer commandBuffer;
    };
}