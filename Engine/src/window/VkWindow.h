#pragma once

#include "Window.h"
#include <vulkan/vulkan.hpp>
#include "VulkanContext.h"

#include <vector>

struct GLFWwindow;

namespace Azazel
{
    struct QueueFamilyIndices 
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() 
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

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
        GLFWwindow* initGLFW(int width, int height, const std::string& title);
        void initGLFWCallbacks(GLFWwindow*);

        void initVulkan();

        VkInstance createVkInstance();
        VkApplicationInfo createVkApplicationInfo(const char* applicationName, const char* engineName);
        VkInstanceCreateInfo createVkInstanceCreateInfo(VkApplicationInfo* appInfo, std::vector<const char*>&, std::vector<const char*>&);
        VkDebugUtilsMessengerEXT setupDebugMessenger(VkInstance);
        VkDebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo(PFN_vkDebugUtilsMessengerCallbackEXT callback);

        VkSurfaceKHR createSurface(VkInstance instance, GLFWwindow* window);

        VkPhysicalDevice createVkPhysicalDevice(VkInstance instance);
        VkDevice createVkDevice(VkPhysicalDevice physicalDevice);

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        VkPhysicalDevice pickPhysicalDevice(VkInstance instance);
        bool isDeviceSuitable(VkPhysicalDevice device);

        VkDevice createLogicalDevice(VkPhysicalDevice physicalDevice);

        VkSwapchainKHR createSwapChain(VkPhysicalDevice physicalDevice);
        
        std::vector<VkImageView> createImageViews(VkDevice, std::vector<VkImage>&);
        VkRenderPass createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
        void createGraphicsPipeline(VkDevice device);
        VkBuffer createVertexBuffer();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void drawFrame() override;

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
        std::vector<const char*> getRequiredExtensions();
        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

        void createFramebuffers();

        VkCommandPool createCommandPool();
        VkCommandBuffer createCommandBuffer();

        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();
        bool checkValidationLayerSupport();

        void destroyGLFW();
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

        // INSTANCE
        VkInstance instance;

        // DEBUG
        VkDebugUtilsMessengerEXT debugMessenger;

        // SURFACE
        VkSurfaceKHR surface;

        // DEVICES
        VkPhysicalDevice physicalDevice;
        VkDevice device;

        // QUEUES
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        // SWAPCHAIN
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;
        VkCommandBuffer commandBuffer;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        VkDescriptorPool descriptorPool;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
    };
}
