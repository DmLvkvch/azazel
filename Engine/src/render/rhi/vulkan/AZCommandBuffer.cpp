#include "AZCommandBuffer.h"

namespace Azazel
{

    AZCommandPool::AZCommandPool(VkDevice device, int queueIndex)
    {
        VkCommandPoolCreateInfo poolInfo {};
        
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueIndex;
        
        vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
    }

    void AZCommandPool::reset()
    {
        vkResetCommandPool(device, commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    }
    
    void AZCommandPool::destroy()
    {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    ////////////////////////////

    AZCommandBuffer::AZCommandBuffer()
    {
    }

    AZCommandBuffer::AZCommandBuffer(VkDevice device, VkCommandPool commandPool)
    {
        VkCommandBufferAllocateInfo allocInfo {};
        
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
    }
    AZCommandBuffer::~AZCommandBuffer()
    {
    }

    void AZCommandBuffer::init()
    {
    }

    void AZCommandBuffer::begin()
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(commandBuffer, &beginInfo);
    }

    void AZCommandBuffer::end()
    {
        vkEndCommandBuffer(commandBuffer);
    }

    void AZCommandBuffer::reset()
    {
        vkResetCommandBuffer(commandBuffer, 0);
    }

    void* AZCommandBuffer::getAPIBuffer()
    {
        return (void*)&commandBuffer;
    }
}