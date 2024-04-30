#include "AZCommandBuffer.h"
#include "AZDevice.h"

namespace Azazel
{

    AZCommandPool::AZCommandPool(const VulkanDevice& device, int queueIndex)
    :device(device)
    {
        VkCommandPoolCreateInfo poolInfo {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueIndex;
        vkCreateCommandPool(device.device, &poolInfo, nullptr, &commandPool);
    }

    AZCommandPool::~AZCommandPool()
    {
        destroy();
    }

    AZCommandBuffer* AZCommandPool::allocateCommandBuffer(const VulkanDevice& device)
    {
        return new AZCommandBuffer(device, *this);
    }

    void AZCommandPool::reset()
    {
        vkResetCommandPool(device.device, commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    }
    
    void AZCommandPool::destroy()
    {
        vkDestroyCommandPool(device.device, commandPool, nullptr);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    AZCommandBuffer::AZCommandBuffer()
    {
    }

    AZCommandBuffer::AZCommandBuffer(const VulkanDevice& device, const AZCommandPool& commandPool)
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

    void AZCommandBuffer::begin() const
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(commandBuffer, &beginInfo);
    }

    void AZCommandBuffer::end() const
    {
        vkEndCommandBuffer(commandBuffer);
    }

    void AZCommandBuffer::reset() const
    {
        vkResetCommandBuffer(commandBuffer, 0);
    }

    void* AZCommandBuffer::getAPIBuffer()
    {
        return (void*)&commandBuffer;
    }

    VkCommandBuffer AZCommandBuffer::beginSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool)
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

    void AZCommandBuffer::endSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool, const VkCommandBuffer commandBuffer)
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