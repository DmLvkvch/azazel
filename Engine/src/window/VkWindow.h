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
        void setupDebugMessenger(VkInstance);

        VkPhysicalDevice initVkPhysicalDevice(VkInstance instance);
        VkDevice initVkDevice(VkPhysicalDevice physicalDevice);

        VkSurfaceKHR createSurface(VkInstance instance, GLFWwindow* window);
        VkPhysicalDevice pickPhysicalDevice(VkInstance instance);
        VkDevice createLogicalDevice(VkPhysicalDevice physicalDevice);
        VkSwapchainKHR createSwapChain(VkPhysicalDevice physicalDevice);
        void recreateSwapChain();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        
        VkDebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo();
        bool isDeviceSuitable(VkPhysicalDevice device);


        std::vector<VkImageView> createImageViews(VkDevice, std::vector<VkImage>&);
        VkRenderPass createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
        void createGraphicsPipeline(VkDevice device);

        void drawFrame() override;

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
        std::vector<const char*> getRequiredExtensions();
        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);


        void createFramebuffers();
        void createCommandPool();

        void createCommandBuffer();
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

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

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
    };
}
