#include "AZContext.h"

#include <memory>

#include "window/Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

#include <vk_mem_alloc.h>

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
        swapChain->initSwapChainFramebuffers(*renderPass);

        commandPool = std::make_unique<AZCommandPool>(*device, physicalDevice->getQueueFamilyIndices().graphicsFamily.value());
        commandBuffer = std::unique_ptr<AZCommandBuffer>(commandPool->allocateCommandBuffer(*device));

        descriptorPool = std::make_unique<AZDescriptorPool>(*device);

        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.vulkanApiVersion = VK_MAKE_VERSION(1, 0, 0);
        allocatorInfo.physicalDevice = physicalDevice->get();
        allocatorInfo.device = device->device;
        allocatorInfo.instance = instance->instance;
        vmaCreateAllocator(&allocatorInfo, &this->allocator);
    }

}