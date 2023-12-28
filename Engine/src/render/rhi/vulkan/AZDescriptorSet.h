#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZDescriptorPool
    {
    public:
        AZDescriptorPool()
        {

        }

        AZDescriptorPool(VkDevice device, uint32_t descriptorCount)
        {
            VkDescriptorPoolSize poolSize {};
            poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            poolSize.descriptorCount = descriptorCount;

            VkDescriptorPoolCreateInfo poolInfo {};
            poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            poolInfo.poolSizeCount = 1;
            poolInfo.pPoolSizes = &poolSize;
            poolInfo.maxSets = descriptorCount;
            vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool);
        }

        ~AZDescriptorPool()
        {

        }

        VkDescriptorPool descriptorPool;
    };

    class DescriptorSet
    {

    };
}