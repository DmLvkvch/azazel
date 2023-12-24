#pragma once

#include "vk_headers.h"
#include "AZCommandBuffer.h"

namespace Azazel
{
    class AZAttachmentDesc
    {

    };

    class AZRenderPassDesc
    {

    };

    class AZRenderPass
    {
    public:
        AZRenderPass()
        {
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