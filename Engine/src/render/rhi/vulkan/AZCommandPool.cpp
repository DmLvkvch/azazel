#include "AZCommandPool.h"

namespace Azazel
{
    AZCommandPool::AZCommandPool(VkDevice device, int queueIndex)
    {
        VkCommandPoolCreateInfo poolInfo{};
        {
            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            poolInfo.queueFamilyIndex = queueIndex;
        }
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
}