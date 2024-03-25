#include "AZContext.h"

#include <memory>

#include "window/Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

namespace Azazel
{
    static AZContext* context = nullptr;
    static ImGui_ImplVulkanH_Window imguiVulkan;


    void setVulkanContext(AZContext& ctx)
    {
        context = std::addressof(ctx);
    }

    AZContext& getVulkanContext()
    {
        return *context;
    }

    void AZContext::init(Window& window)
    {
        instance = std::make_unique<AZInstance>();
        surface = std::make_unique<AZSurface>(instance->instance, static_cast<GLFWwindow*>(window.getNativeWindow()));
        physicalDevice = std::make_unique<PhysicalDevice>(instance->instance, surface->surface);
        device = std::make_unique<VulkanDevice>(*instance, *physicalDevice);
        swapChain = std::make_unique<AZSwapChain>(static_cast<GLFWwindow*>(window.getNativeWindow()), *surface, *physicalDevice, *device);
        renderPass = std::make_unique<AZRenderPass>(device->device, swapChain->swapChainImageFormat);

        auto& swapChainImageViews = swapChain->swapChainImageViews;
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++)
        {
            uint32_t width = swapChain->swapChainExtent.width;
            uint32_t height = swapChain->swapChainExtent.height;
            auto& imageView = swapChainImageViews[i];
            AZFramebufferDesc fboDesc{ {imageView}, renderPass->renderPass, width, height };
            swapChainFramebuffers[i] = AZFramebuffer(device->device, fboDesc);
        }

        commandPool = std::make_unique<AZCommandPool>(*device, physicalDevice->indices.graphicsFamily.value());

        descriptorPool = std::make_unique<AZDescriptorPool>(*device);
    }

}