#pragma once

#include "vk_headers.h"
#include "AZCommandBuffer.h"

namespace Azazel
{
    class VulkanDevice;

    template <size_t T>
    struct AZAttachmentDesc
    {
        std::array<VkAttachmentDescription, T> attachments;
        AZAttachmentDesc& addAttachment(int index, VkFormat format)
        {

        }
    };

    struct AZSubpassDesc
    {

    };

    struct AZRenderPassDesc
    {
    
    };

    class AZRenderPass
    {
    public:
        AZRenderPass(const VulkanDevice& device, VkFormat format);

        ~AZRenderPass();

        void initRenderPass(VkFormat format);

        void beginRenderPass(const AZCommandBuffer& commandBuffer, VkFramebuffer framebuffer, VkExtent2D extent) const;

        void endRenderPass(const AZCommandBuffer& commandBuffer) const;

        void destroy();

        const VulkanDevice& device;
        VkRenderPass renderPass;
        vk::RenderPass vkRenderPass;
    };
}