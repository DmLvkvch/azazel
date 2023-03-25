#pragma once

#include "Window.h"
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Azazel
{
    class VkWindow : public Window
    {
    public:
        VkWindow(const WindowProperties& props);
        virtual ~VkWindow();
        void shutDown();
        void onUpdate(float delta) override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;
        virtual void setEventCallback(const EventCallbackFn& callback) override;
        virtual void setVSync(bool enable) override;
        virtual bool isVSync() const override;
        virtual void* getNativeWindow() override;
    private:
        void destroyGLFW();
        void destroyImgui();
        void createInstance();

        void initVulkan();

		void createDebugCallback();
		void findPhysicalDevice();
		void findQueueFamilies();

		void createWindowSurface();
		void checkSwapChainSupport();
		void createLogicalDevice();
		void createSemaphores();
		void createCommandPool();
        
        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initImgui(GLFWwindow* window, int width, int height);
    private:
        GLFWwindow* window;
        int width;
        int height;
        std::string title;

        struct WindowData
        {
            EventCallbackFn eventCallback;
        };

        WindowData windowData;

        VkInstance instance;
        VkSurfaceKHR windowSurface;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkDebugReportCallbackEXT callback;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderingFinishedSemaphore;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        VkVertexInputBindingDescription vertexBindingDescription;
        std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;


        VkBuffer uniformBuffer;
        VkDeviceMemory uniformBufferMemory;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
        VkDescriptorSet descriptorSet;

        VkExtent2D swapChainExtent;
        VkFormat swapChainFormat;
        VkSwapchainKHR oldSwapChain;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
        VkPipelineLayout pipelineLayout;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> graphicsCommandBuffers;

        uint32_t graphicsQueueFamily;
        uint32_t presentQueueFamily;

    };
}