#include "AZContext.h"

#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

namespace Azazel
{
    static AZContext* context = nullptr;

    void setVulkanContext(AZContext& ctx)
    {
        context = std::addressof(ctx);
    }

    AZContext& getVulkanContext()
    {
        return *context;
    }

    static ImGui_ImplVulkanH_Window g_MainWindowData;

    void ImGuiContext::init(GLFWwindow* window)
    {
        // VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        // g_MainWindowData.Surface = surface->surface;
        // g_MainWindowData.SurfaceFormat = swapChain->surfaceFormat;
        // g_MainWindowData.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(physicalDevice->physicalDevice, surface->surface, &presentMode, 1);
        // ImGui_ImplVulkanH_CreateOrResizeWindow(instance->instance, physicalDevice->physicalDevice, device->device, &g_MainWindowData, device->graphicsQueue.queueFamilyIndex, nullptr, width, height, 2);

        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGuiIO& io = ImGui::GetIO(); (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // ImGui::StyleColorsDark();

        // ImGui_ImplGlfw_InitForVulkan(window, true);
        // ImGui_ImplVulkan_InitInfo init_info{};
        // init_info.Instance = instance->instance;
        // init_info.PhysicalDevice = physicalDevice->physicalDevice;
        // init_info.Device = device->device;
        // init_info.QueueFamily = device->graphicsQueue.queueFamilyIndex;
        // init_info.Queue = device->graphicsQueue.queue;
        // init_info.PipelineCache = nullptr;
        // init_info.DescriptorPool = descriptorPool;
        // init_info.Subpass = 0;
        // init_info.RenderPass = g_MainWindowData.RenderPass;
        // init_info.MinImageCount = 2;
        // init_info.ImageCount = g_MainWindowData.ImageCount;
        // init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        // init_info.Allocator = nullptr;
        // init_info.CheckVkResultFn = nullptr;
        // ImGui_ImplVulkan_Init(&init_info);
    }

}