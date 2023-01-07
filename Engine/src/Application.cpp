#include "Application.h"
#include "events/ApplicationEvent.h"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <renderer/Render.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

namespace Azazel
{
    Application* Application::app = nullptr;

    Application* Application::getApplication()
    {
        if (!Application::app)
        {
            Application::app = new Application();
        }
        return Application::app;
    }

    Application::Application()
    {
        lastFrameTime = 0.0f;
        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        Render::getRenderer()->init();
    }

    Application::~Application()
    {
        
    }

    void Application::onEvent(Event& e)
    {
        if (e.getEventType() == EventType::WindowClose)
        {
            running = false;
        }

        for (auto it = layerStack.end(); it != layerStack.begin(); )
        {
            (*(--it))->onEvent(e);
        }
    }

    void Application::run()
    {
        while (running)
        {
            float t = (float) (glfwGetTime() * 1000);
            float delta = t - lastFrameTime;
            lastFrameTime = t;
            Render::getRenderer()->beginScene();
            Render::getRenderer()->setClearColor({0.0f, 0.0f, 0.0f, 1.0f});
            Render::getRenderer()->clear(true, true, false);
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();
            for (auto layer : layerStack)
            {
                layer->onInputUpdate(delta);
                layer->onUpdate(delta);
            }
            for (auto layer : layerStack)
            {
                layer->onImguiRender(delta);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window->onUpdate(delta);
            Render::getRenderer()->endScene();
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* layer)
    {
        layerStack.pushOverlay(layer);
    }

    Window* Application::getWindow()
    {
        return this->window.get();
    }
}