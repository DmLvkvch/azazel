#include "Application.h"
#include "events/ApplicationEvent.h"
#include "render/Render.h"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

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

    void Application::subscribe(std::function<void(float)> func)
    {
        this->subscribers.push_back(func);
    }

    void Application::updateTargets(float delta)
    {
        for (auto& subscriber : subscribers)
        {
            subscriber(delta);
        }
    }

    Application::Application()
    {
        delta = 0.0f;
        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        Render::getRender()->init();
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

        for (auto layer : layerStack)
        {
            layer->onEvent(e);
        }
    }

    void Application::run()
    {
        while (running)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            
            Render::getRender()->beginScene();
            Render::getRender()->setClearColor({0.0f, 0.0f, 0.0f, 1.0f});
            Render::getRender()->clear(true, true, false);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            for (auto layer : layerStack)
            {
                layer->onInputUpdate(delta);
                layer->onImguiRender(delta);
                layer->onUpdate(delta);
                layer->onRender(delta);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            window->onUpdate(delta);
            Render::getRender()->endScene();
            auto stopTime = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    Window* Application::getWindow()
    {
        return this->window.get();
    }
}