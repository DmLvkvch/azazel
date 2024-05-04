#pragma once

#include "vk_headers.h"
#include <vulkan/vulkan.hpp>
#include "AZDevice.h"

namespace Azazel
{
    struct AZFramebufferDesc
    {
        std::vector<VkImageView> attachments;
        VkRenderPass renderPass;
        uint32_t width;
        uint32_t height;
    };

    class AZFramebuffer
    {
    public:
        AZFramebuffer()
            : framebuffer(vk::Framebuffer{})
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
}