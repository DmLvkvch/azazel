#include "VkWindow.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <iostream>
#include <vector>

namespace Azazel
{
    static bool initialized = false;

    VkWindow::VkWindow(const WindowProperties& props)
    {
        if (initialized)
        {
            return;
        }
        
        width = props.width;
        height = props.height;
        title = props.title;

        // INIT GLFW
        GLFWwindow* window = initGLFW(width, height, title);

        // INIT GLAD
        //if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        //{
        //    std::cout << "Failed to initialize GLAD" << std::endl;
        //}

        //INIT IMGUI
        initImgui(window, width, height);

        // SET GLFW/ImGUi callbacks
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent e;
            data.eventCallback(e);
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowResizeEvent e(w, h);
            data.eventCallback(e);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            //ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent e(key, 1);
                    data.eventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    data.eventCallback(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e(key, 1);
                    data.eventCallback(e);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            //ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent e(button);
                    data.eventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent e(button);
                    data.eventCallback(e);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            //ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent e((float) xOffset, (float) yOffset);
            data.eventCallback(e);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            //ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent e((float) xPos, (float) yPos);
            data.eventCallback(e);
        });

        createInstance();
    }

    void VkWindow::initVulkan()
    {
        createInstance();
    }

    void VkWindow::createInstance()
    {
        VkApplicationInfo appInfo {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Azazel Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Azazel Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

	void VkWindow::createDebugCallback()
    {
        // TODO
    }

	void VkWindow::findPhysicalDevice()
    {
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0)
        {
            std::cout<<"vulkan doesnt support!"<<std::endl;
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        physicalDevice = devices[0];
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
    }

	void VkWindow::findQueueFamilies()
    {
        uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		if (queueFamilyCount == 0)
        {
			std::cout << "physical device has no queue families!" << std::endl;
			exit(1);
		}

		// Find queue family with graphics support
		// Note: is a transfer queue necessary to copy vertices to the gpu or can a graphics queue handle that?
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

		std::cout << "physical device has " << queueFamilyCount << " queue families" << std::endl;

		bool foundGraphicsQueueFamily = false;
		bool foundPresentQueueFamily = false;

		for (uint32_t i = 0; i < queueFamilyCount; i++)
        {
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, windowSurface, &presentSupport);

			if (queueFamilies[i].queueCount > 0 && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
				graphicsQueueFamily = i;
				foundGraphicsQueueFamily = true;

				if (presentSupport)
                {
					presentQueueFamily = i;
					foundPresentQueueFamily = true;
					break;
				}
			}

			if (!foundPresentQueueFamily && presentSupport)
            {
				presentQueueFamily = i;
				foundPresentQueueFamily = true;
			}
		}

		if (foundGraphicsQueueFamily)
        {
			std::cout << "queue family #" << graphicsQueueFamily << " supports graphics" << std::endl;

			if (foundPresentQueueFamily) 
            {
				std::cout << "queue family #" << presentQueueFamily << " supports presentation" << std::endl;
			} else
            {
				std::cerr << "could not find a valid queue family with present support" << std::endl;
				exit(1);
			}
		}
        else
        {
			std::cerr << "could not find a valid queue family with graphics support" << std::endl;
			exit(1);
		}
    }

    void VkWindow::createLogicalDevice() {
		// Greate one graphics queue and optionally a separate presentation queue
		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo queueCreateInfo[2] = {};

		queueCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo[0].queueFamilyIndex = graphicsQueueFamily;
		queueCreateInfo[0].queueCount = 1;
		queueCreateInfo[0].pQueuePriorities = &queuePriority;

		queueCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo[0].queueFamilyIndex = presentQueueFamily;
		queueCreateInfo[0].queueCount = 1;
		queueCreateInfo[0].pQueuePriorities = &queuePriority;

		// Create logical device from physical device
		// Note: there are separate instance and device extensions!
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;

		if (graphicsQueueFamily == presentQueueFamily) {
			deviceCreateInfo.queueCreateInfoCount = 1;
		} else {
			deviceCreateInfo.queueCreateInfoCount = 2;
		}

		// Necessary for shader (for some reason)
		VkPhysicalDeviceFeatures enabledFeatures = {};
		enabledFeatures.shaderClipDistance = VK_TRUE;
		enabledFeatures.shaderCullDistance = VK_TRUE;

		const char* deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
		deviceCreateInfo.enabledExtensionCount = 1;
		deviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions;
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

		if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
			std::cerr << "failed to create logical device" << std::endl;
			exit(1);
		}

		std::cout << "created logical device" << std::endl;

		// Get graphics and presentation queues (which may be the same)
		vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
		vkGetDeviceQueue(device, presentQueueFamily, 0, &presentQueue);

		std::cout << "acquired graphics and presentation queues" << std::endl;

		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemoryProperties);

        {
            VkDescriptorPoolSize pool_sizes[] =
            {
                { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
            };
            VkDescriptorPoolCreateInfo pool_info = {};
            pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
            pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
            pool_info.pPoolSizes = pool_sizes;
            VkResult err = vkCreateDescriptorPool(device, &pool_info, nullptr, &descriptorPool);
        }
	}

	void VkWindow::createSemaphores() {
		VkSemaphoreCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(device, &createInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(device, &createInfo, nullptr, &renderingFinishedSemaphore) != VK_SUCCESS) {
			std::cerr << "failed to create semaphores" << std::endl;
			exit(1);
		} else {
			std::cout << "created semaphores" << std::endl;
		}
	}

	void VkWindow::createCommandPool() {
		// Create graphics command pool
		VkCommandPoolCreateInfo poolCreateInfo = {};
		poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolCreateInfo.queueFamilyIndex = graphicsQueueFamily;

		if (vkCreateCommandPool(device, &poolCreateInfo, nullptr, &commandPool) != VK_SUCCESS) {
			std::cerr << "failed to create command queue for graphics queue family" << std::endl;
			exit(1);
		} else {
			std::cout << "created command pool for graphics queue family" << std::endl;
		}
	}
	

    bool isDeviceSutable(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
    }

    VkWindow::~VkWindow()
    {
        shutDown();
    }

    GLFWwindow* VkWindow::initGLFW(int width, int height, const std::string& title)
    {
        int succes = glfwInit();
        if (succes == GLFW_FALSE)
        {
            std::cout << "Failed to initialize" << std::endl;
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
       // glfwWindowHint(GLFW_SAMPLES, 4);
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        setVSync(true);
        glfwSetWindowUserPointer(window, &windowData);
        initialized = true;
        return window;
    }

    void VkWindow::destroyGLFW()
    {

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void VkWindow::initImgui(GLFWwindow* window, int width, int height)
    {

        VkDescriptorPoolSize pool_sizes[] =
        {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000;
        //pool_info.poolSizeCount = std::size(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;

        VkDescriptorPool imguiPool;
        //VK_CHECK(vkCreateDescriptorPool(_device, &pool_info, nullptr, &imguiPool));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        ImGui::StyleColorsDark();

        io.DisplaySize = ImVec2((float)width, (float)height);
        //ImGui_ImplGlfw_InitForVulkan(window, true);
        //  ImGui_ImplVulkan_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

        ImGui_ImplVulkan_InitInfo init_info = {};
        //init_info.Instance = _instance;
        //init_info.PhysicalDevice = _chosenGPU;
        //init_info.Device = _device;
        //init_info.Queue = _graphicsQueue;
        init_info.DescriptorPool = imguiPool;
        init_info.MinImageCount = 3;
        init_info.ImageCount = 3;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

        //ImGui_ImplVulkan_Init(&init_info, _renderPass);

        //execute a gpu command to upload imgui font textures
        //immediate_submit([&](VkCommandBuffer cmd) {
        //    ImGui_ImplVulkan_CreateFontsTexture(cmd);
        //    });

        //clear font textures from cpu data
        //ImGui_ImplVulkan_DestroyFontUploadObjects();

        //add the destroy the imgui created structures
        //_mainDeletionQueue.push_function([=]() {
//
        //    vkDestroyDescriptorPool(_device, imguiPool, nullptr);
        //    ImGui_ImplVulkan_Shutdown();
        //    });
    }

    void VkWindow::destroyImgui()
    {
        //ImGui_ImplVulkan_Shutdown();
        //ImGui_ImplGlfw_Shutdown();
        //ImGui::DestroyContext();
    }

    void VkWindow::shutDown()
    {
        vkDestroyInstance(instance, nullptr);
        destroyImgui();
        destroyGLFW();
    }

    void VkWindow::onUpdate(float delta)
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    unsigned int VkWindow::getWidth() const
    {
        return width;
    }

    unsigned int VkWindow::getHeight() const
    {
        return height;
    }

    void VkWindow::setEventCallback(const EventCallbackFn& callback)
    {
        this->windowData.eventCallback = callback;
    }

    void VkWindow::setVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool VkWindow::isVSync() const
    {
        return true;
    }

    void* VkWindow::getNativeWindow()
    {
        return (void*) window;
    }
}