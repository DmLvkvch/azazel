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

        void beginRenderPass(const AZCommandBuffer& commandBuffer, VkFramebuffer framebuffer, VkExtent2D extent) const;

        void endRenderPass(const AZCommandBuffer& commandBuffer) const;

        void destroy();

        VkRenderPass renderPass;
    };
}