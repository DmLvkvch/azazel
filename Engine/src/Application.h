#pragma once

#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include <functional>

namespace Azazel
{
    class Application
    {
    public:
        Application();
        ~Application();
        void run();
        void onEvent(Event& e);
        void pushLayer(Layer* layer);
        Window* getWindow();
        static Application* getApplication();
        std::vector<std::function<void(float)>> subscribers;
    private:
        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running = true;
        static Application* app;
        float lastFrameTime;
    };
}