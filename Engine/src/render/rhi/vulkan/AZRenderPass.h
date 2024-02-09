#pragma once

#include "vk_headers.h"
#include "AZCommandBuffer.h"

namespace Azazel
{
    struct AZAttachmentDesc
    {

    };

    struct AZRenderPassDesc
    {

    };

    class AZRenderPass
    {
    public:
        AZRenderPass(VkDevice device, VkFormat format)
        {
            initRenderPass(device, format);
        }

        ~AZRenderPass()
        {
        }

        void initRenderPass(VkDevice device, VkFormat format);

        void beginRenderPass(AZCommandBuffer& commandBuffer, VkFramebuffer& framebuffer, VkExtent2D extent);

        void endRenderPass(AZCommandBuffer& commandBuffer);

        void destroy()
        {
            vkDestroyRenderPass(nullptr, renderPass, nullptr);
        }

        VkRenderPass renderPass;
    };
}