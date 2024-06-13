#include "AZDescriptorSet.h"

#include "AZDevice.h"

namespace Azazel
{
    AZDescriptorPool::AZDescriptorPool(VulkanDevice& device)
    {
        std::array<VkDescriptorPoolSize, 11> pool_sizes 
        {{
            {VK_DESCRIPTOR_TYPE_SAMPLER, 2048},
            {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2048},
            {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 2048},
            {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 2048}
        }};
        VkDescriptorPoolCreateInfo poolInfo {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 2048 * pool_sizes.size();
        poolInfo.poolSizeCount = pool_sizes.size();
        poolInfo.pPoolSizes = pool_sizes.data();
        vkCreateDescriptorPool(device.device, &poolInfo, nullptr, &descriptorPool);
    }
}