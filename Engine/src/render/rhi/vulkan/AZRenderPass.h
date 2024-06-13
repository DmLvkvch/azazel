#pragma once

#include "vk_headers.h"
#include "AZCommandBuffer.h"

namespace Azazel
{
    class VulkanDevice;

    struct AZFramebufferDesc
    {
        std::vector<vk::ImageView> attachments;
        vk::RenderPass renderPass;
        uint32_t width;
        uint32_t height;
    };

    class AZFramebuffer
    {
    public:
        AZFramebuffer()
        : framebuffer(vk::Framebuffer {})
        {
        }

        AZFramebuffer(VulkanDevice& device, AZFramebufferDesc& framebufferDesc);
        
        AZFramebuffer(const AZFramebuffer& fb)
        : framebuffer(fb.framebuffer)
        {
        }

        AZFramebuffer& operator=(const AZFramebuffer& fb)
        {
            framebuffer = fb.framebuffer;
            return *this;
        }

        ~AZFramebuffer()
        {

        }

        void destroy()
        {
            //device.device.destroyFramebuffer(framebuffer);
        }

        VkFramebuffer get()
        {
            return framebuffer;
        }
        
        vk::Framebuffer framebuffer;
    };

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
        AZRenderPass(const VulkanDevice& device, vk::Format format);

        ~AZRenderPass();

        void initRenderPass(vk::Format format);

        void beginRenderPass(const AZCommandBuffer& commandBuffer, vk::Framebuffer framebuffer, vk::Extent2D extent) const;

        void endRenderPass(const AZCommandBuffer& commandBuffer) const;

        void destroy();

        const VulkanDevice& device;
        vk::RenderPass renderPass;
    };
}