#include "AZCommandBuffer.h"
#include "AZDevice.h"

namespace Azazel
{

    AZCommandPool::AZCommandPool(const VulkanDevice& device, int queueIndex)
    : device(device)
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
        vk::CommandBuffer commandBuffer {};
        vk::CommandBufferAllocateInfo allocInfo {};
        allocInfo.setCommandPool(commandPool).setLevel(vk::CommandBufferLevel::ePrimary).setCommandBufferCount(1);
        std::ignore = device.device.allocateCommandBuffers(&allocInfo, &commandBuffer);
        return commandBuffer;
    }

    void AZCommandPool::reset()
    {
        device.device.resetCommandPool(commandPool, vk::CommandPoolResetFlagBits::eReleaseResources);
    }
    
    void AZCommandPool::destroy()
    {
        device.device.destroyCommandPool(commandPool);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    AZCommandBuffer::AZCommandBuffer()
    {
    }

    AZCommandBuffer::AZCommandBuffer(vk::CommandBuffer commandBuffer)
    : commandBuffer(commandBuffer)
    {
    }

    AZCommandBuffer::~AZCommandBuffer()
    {
    }

    void AZCommandBuffer::begin() const
    {
        vk::CommandBufferBeginInfo beginInfo{};
        beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
        commandBuffer.begin(beginInfo);
    }

    void AZCommandBuffer::end() const
    {
        commandBuffer.end();
    }

    void AZCommandBuffer::reset() const
    {
        commandBuffer.reset();
    }

    void* AZCommandBuffer::getAPIBuffer()
    {
        return (void*)&commandBuffer;
    }

    vk::CommandBuffer AZCommandBuffer::beginSingleTimeCommands(const VulkanDevice& device, const AZCommandPool& commandPool)
    {
        vk::CommandBufferAllocateInfo allocInfo{};
        allocInfo.setLevel(vk::CommandBufferLevel::ePrimary).setCommandPool(commandPool.commandPool).setCommandBufferCount(1);

        vk::CommandBuffer commandBuffer {};
        (void)device.device.allocateCommandBuffers(&allocInfo, &commandBuffer);

        vk::CommandBufferBeginInfo beginInfo{};
        beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
        commandBuffer.begin(beginInfo);
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