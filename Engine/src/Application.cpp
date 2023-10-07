#include "Application.h"
#include "events/ApplicationEvent.h"
#include "render/Render.h"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_vulkan.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "events/Event.h"

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

    unsigned long long Application::subscribe(const std::function<void(Event&)>& func)
    {
        return this->eventSubscribers.addListener(func);
    }

    unsigned long long Application::subscribe(const std::function<void(float)>& func)
    {
        return this->updateSubscribers.addListener(func);
    }

    void Application::unsubscribe(long long id)
    {
        if (id <= 0)
        {
            return;
        }
        eventSubscribers.removeListener(id);
        updateSubscribers.removeListener(id);
    }

    void Application::updateTargets(float delta)
    {
        updateSubscribers.dispatch(delta);
    }

    Application::Application()
    {
        delta = 0.0f;
        window.reset(Window::create());
        window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        Render::getRender()->init();
        camera.reset(new Camera());
        Render::getRender()->setCamera(camera.get());
        Render::getRender()->setDefaultViewport( Viewport{0, 0, (int) window->getWidth() * 2, (int) window->getHeight() * 2} );
    }

    Application::~Application()
    {
        eventSubscribers.clear();
        updateSubscribers.clear();
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
        eventSubscribers.dispatch(e);
        camera->onEvent(e);
    }

    void Application::run()
    {
        while (running)
        {
            window->onUpdate(delta);
            window->drawFrame();

            auto startTime = std::chrono::high_resolution_clock::now();
            Render::getRender()->setViewport(0, 0, window->getWidth() * 2, window->getHeight() * 2);
            Render::getRender()->beginScene();
            Render::getRender()->setClearColor({1.0f, 1.0f, 0.0f, 1.0f});
            Render::getRender()->clear(true, true, false);

            #ifdef AZAZEL_GL
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();
            #else
            //ImGui_ImplVulkan_NewFrame();
            //ImGui::NewFrame();
            #endif
            
            updateTargets(delta);
            camera->onInputUpdate(delta);
            for (auto layer : layerStack)
            {
                layer->onInputUpdate(delta);
                layer->onImguiRender(delta);
                layer->onUpdate(delta);
                layer->onRender(delta);
            }
            
            #ifdef AZAZEL_GL
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            #else
            //ImGui::Render();
            //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
            #endif

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