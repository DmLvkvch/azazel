#include "AZCommandBuffer.h"
#include "AZDevice.h"

namespace Azazel
{

    AZCommandPool::AZCommandPool(VulkanDevice& device, int queueIndex)
    {
        VkCommandPoolCreateInfo poolInfo {};
        
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueIndex;
        
        vkCreateCommandPool(device.device, &poolInfo, nullptr, &commandPool);
    }

    AZCommandBuffer* AZCommandPool::allocateCommandBuffer(VulkanDevice& device)
    {
        return new AZCommandBuffer(device, *this);
    }

    void AZCommandPool::reset()
    {
        vkResetCommandPool(device, commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    }
    
    void AZCommandPool::destroy()
    {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    AZCommandBuffer::AZCommandBuffer()
    {
    }

    AZCommandBuffer::AZCommandBuffer(VulkanDevice& device, AZCommandPool& commandPool)
    {
        VkCommandBufferAllocateInfo allocInfo {};
        
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool.commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        
        vkAllocateCommandBuffers(device.device, &allocInfo, &commandBuffer);
    }
    AZCommandBuffer::~AZCommandBuffer()
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

    VkCommandBuffer AZCommandBuffer::beginSingleTimeCommands(VulkanDevice& device, AZCommandPool & commandPool)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool.commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device.device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void AZCommandBuffer::endSingleTimeCommands(VulkanDevice& device, AZCommandPool& commandPool, VkCommandBuffer commandBuffer)
    {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(device.graphicsQueue.queue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(device.graphicsQueue.queue);

        vkFreeCommandBuffers(device.device, commandPool.commandPool, 1, &commandBuffer);
    }
}