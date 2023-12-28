#pragma once

#include "vk_headers.h"

namespace Azazel
{
    class AZDescriptorSetLayout
    {
    public:
        AZDescriptorSetLayout()
        {

        }

        AZDescriptorSetLayout(VKDevice device)
        {
            VkDescriptorSetLayoutBinding layoutBinding {};
            uboLayoutBinding.binding = 0;
            uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            uboLayoutBinding.descriptorCount = 1;
            uboLayoutBinding.pImmutableSamplers = nullptr;
            uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

            VkDescriptorSetLayoutCreateInfo layoutInfo {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = 1;
            layoutInfo.pBindings = &layoutBinding;

            vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout);
        }

        ~AZDescriptorSetLayout()
        {

        }

        VkDescriptorSetLayout descriptorSetLayout;
    };

    class AZGraphicsPipeline
    {

    };
}