#include "WindowsWindow.h"

#include <iostream>
#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Azazel
{
    static bool initialized = false;

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        if (initialized)
        {
            return;
        }
        
        width = props.width;
        height = props.height;
        title = props.title;
        int succes = glfwInit();
        if (succes == GLFW_FALSE)
        {
            std::cout << "Failed to initialize" << std::endl;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, 1);
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        setVSync(true);
        glfwSetWindowUserPointer(window, &windowData);
        initialized = true;
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		ImGui::StyleColorsDark();
;
		io.DisplaySize = ImVec2((float)width, (float)height);
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

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
            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            std::cout<<"key "<<key<<std::endl;
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
            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
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
            ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent e((float) xOffset, (float) yOffset);
            data.eventCallback(e);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent e((float) xPos, (float) yPos);
            data.eventCallback(e);
        });


    }

    WindowsWindow::~WindowsWindow()
    {
        shutDown();
    }

    void WindowsWindow::shutDown()
    {
        glfwDestroyWindow(window);
    }

    void WindowsWindow::onUpdate(float delta)
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    unsigned int WindowsWindow::getWidth() const
    {
        return width;
    }

    unsigned int WindowsWindow::getHeight() const
    {
        return height;
    }

    void WindowsWindow::setEventCallback(const EventCallbackFn& callback)
    {
        this->windowData.eventCallback = callback;
    }

    void WindowsWindow::setVSync(bool enable)
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

    bool WindowsWindow::isVSync() const
    {
        return true;
    }

    void* WindowsWindow::getNativeWindow()
    {
        return (void*) window;
    }
}