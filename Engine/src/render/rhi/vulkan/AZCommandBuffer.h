#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZCommandBuffer
    {
    public:
        AZCommandBuffer()
        {

        }

        AZCommandBuffer(VkDevice device, VkCommandPool commandPool)
        {
            VkCommandBufferAllocateInfo allocInfo {};
            {
                allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.commandPool = commandPool;
                allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandBufferCount = 1;
            }

            if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to allocate command buffers!");
            }
        }

        ~AZCommandBuffer()
        {

        }

        void init()
        {

        }
    
        void begin()
        {
            VkCommandBufferBeginInfo beginInfo {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
        }

        void end()
        {
            vkEndCommandBuffer(commandBuffer);
        }

        void execute()
        {

        }

        void reset()
        {
            vkResetCommandBuffer(commandBuffer, 0);
        }

        void* getAPIBuffer() 
        { 
            return (void*) &commandBuffer; 
        }

    public:
        VkCommandBuffer commandBuffer;
        VkCommandPool   commandPool;
    };
}