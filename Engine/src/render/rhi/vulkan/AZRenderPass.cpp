#include "AZRenderPass.h"
#include "AZDevice.h"

namespace Azazel
{

    AZFramebuffer::AZFramebuffer(VulkanDevice& device, AZFramebufferDesc& framebufferDesc)
    {
        vk::FramebufferCreateInfo framebufferInfo{};
        framebufferInfo.setRenderPass(framebufferDesc.renderPass)
                       .setAttachmentCount(static_cast<uint32_t>(framebufferDesc.attachments.size()))
                       .setPAttachments(framebufferDesc.attachments.data())
                       .setWidth(framebufferDesc.width).setHeight(framebufferDesc.height).setLayers(1);
        framebuffer = device.device.createFramebuffer(framebufferInfo);
    }

    AZRenderPass::AZRenderPass(const VulkanDevice& device, vk::Format format)
    : device(device)
    {
        initRenderPass(format);
    }

    AZRenderPass::~AZRenderPass()
    {
        destroy();
    }
    
    void AZRenderPass::initRenderPass(vk::Format format)
    {
        vk::AttachmentDescription colorAttachment {};
        colorAttachment.setFormat(format).setSamples(vk::SampleCountFlagBits::e1)
                       .setLoadOp(vk::AttachmentLoadOp::eClear).setStoreOp(vk::AttachmentStoreOp::eStore)
                       .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare).setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                       .setInitialLayout(vk::ImageLayout::eUndefined).setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        vk::AttachmentDescription depthAttachment {};
        depthAttachment.setFormat(vk::Format::eD32Sfloat).setSamples(vk::SampleCountFlagBits::e1)
                       .setLoadOp(vk::AttachmentLoadOp::eClear).setStoreOp(vk::AttachmentStoreOp::eDontCare)
                       .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare).setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                       .setInitialLayout(vk::ImageLayout::eUndefined).setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::AttachmentReference colorAttachmentRef {};
        colorAttachmentRef.setAttachment(0)
                          .setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        vk::AttachmentReference depthAttachmentRef {};
        depthAttachmentRef.setAttachment(1)
                          .setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::SubpassDependency dependency {};
        dependency.setSrcSubpass(VK_SUBPASS_EXTERNAL)
                  .setDstSubpass(0)
                  .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests)
                  .setSrcAccessMask(vk::AccessFlagBits::eNone)
                  .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests)
                  .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite);

        vk::SubpassDescription subpass {};
        subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
               .setColorAttachmentCount(1)
               .setPColorAttachments(&colorAttachmentRef)
               .setPDepthStencilAttachment(&depthAttachmentRef);

        std::array<vk::AttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
        vk::RenderPassCreateInfo renderPassInfo {};
        renderPassInfo.setAttachmentCount(static_cast<uint32_t>(attachments.size()))
                      .setPAttachments(attachments.data())
                      .setSubpassCount(1).setPSubpasses(&subpass)
                      .setDependencyCount(1).setPDependencies(&dependency);
        renderPass = device.device.createRenderPass(renderPassInfo);
    }

    void AZRenderPass::beginRenderPass(const AZCommandBuffer& commandBuffer, vk::Framebuffer framebuffer, vk::Extent2D extent) const
    {
        vk::RenderPassBeginInfo renderPassBeginInfo {};
        renderPassBeginInfo.setRenderPass(renderPass).setFramebuffer(framebuffer).setRenderArea({{0, 0}, extent});
        std::array<vk::ClearValue, 2> clearValues {};
        vk::ClearColorValue clearColorValue {0.0f, 0.0f, 0.0f, 0.0f};
        clearValues[0].setColor(clearColorValue);
        clearValues[1].setDepthStencil({1.0f, 0});
        vk::ArrayProxyNoTemporaries vkClearValues {clearValues.size(), clearValues.data()};
        renderPassBeginInfo.setClearValues(vkClearValues);
        commandBuffer.commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
    }

    void AZRenderPass::endRenderPass(const AZCommandBuffer& commandBuffer) const
    {
        commandBuffer.commandBuffer.endRenderPass();
    }

    void AZRenderPass::destroy()
    {
        device.device.destroyRenderPass(renderPass);
    }
}