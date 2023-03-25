#include "GLWindow.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

namespace Azazel
{
    static bool initialized = false;

    GLWindow::GLWindow(const WindowProperties& props)
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
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

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
            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
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
            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
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

    GLWindow::~GLWindow()
    {
        shutDown();
    }

    GLFWwindow* GLWindow::initGLFW(int width, int height, const std::string& title)
    {
        int succes = glfwInit();
        if (succes == GLFW_FALSE)
        {
            std::cout << "Failed to initialize" << std::endl;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 4);
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
        return window;
    }

    void GLWindow::destroyGLFW()
    {

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void GLWindow::initImgui(GLFWwindow* window, int width, int height)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        ImGui::StyleColorsDark();

        io.DisplaySize = ImVec2((float)width, (float)height);
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    }

    void GLWindow::destroyImgui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GLWindow::shutDown()
    {
        destroyImgui();
        destroyGLFW();
    }

    void GLWindow::onUpdate(float delta)
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    unsigned int GLWindow::getWidth() const
    {
        return width;
    }

    unsigned int GLWindow::getHeight() const
    {
        return height;
    }

    void GLWindow::setEventCallback(const EventCallbackFn& callback)
    {
        this->windowData.eventCallback = callback;
    }

    void GLWindow::setVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(GLFW_TRUE);
        }
        else
        {
            glfwSwapInterval(GLFW_FALSE);
        }
    }

    bool GLWindow::isVSync() const
    {
        return true;
    }

    void* GLWindow::getNativeWindow()
    {
        return static_cast<void*>(window);
    }
}