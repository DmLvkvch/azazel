#include "AZCommandBuffer.h"
#include "AZDevice.h"

namespace Azazel
{

    AZCommandPool::AZCommandPool(const VulkanDevice& device, int queueIndex)
    :device(device)
    {
        vk::CommandPoolCreateInfo poolInfo;
        poolInfo.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer).setQueueFamilyIndex(queueIndex);
        commandPool = device.device.createCommandPool(poolInfo);
    }

    AZCommandPool::~AZCommandPool()
    {
        destroy();
    }

    vk::CommandBuffer AZCommandPool::allocateCommandBuffer(const VulkanDevice& device) const
    {
        VkCommandBuffer commandBuffer;
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        vkAllocateCommandBuffers(device.device, &allocInfo, &commandBuffer);
        return commandBuffer;
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

    AZCommandBuffer::AZCommandBuffer(VkCommandBuffer commandBuffer)
        : commandBuffer(commandBuffer)
    {
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

    vk::CommandBuffer AZCommandBuffer::beginSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool)
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

    void AZCommandBuffer::endSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool, const vk::CommandBuffer& commandBuffer)
    {
        commandBuffer.end();
        vk::SubmitInfo submitInfo{};
        submitInfo.setCommandBufferCount(1).setCommandBuffers({ 1, &commandBuffer });
        device.graphicsQueue.queue.submit({ submitInfo });
        device.graphicsQueue.queue.waitIdle();
        device.device.freeCommandBuffers(commandPool.commandPool, { commandBuffer });
    }
}