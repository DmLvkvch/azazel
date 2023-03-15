#pragma once

#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include <functional>
#include <unordered_map>

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

        void subscribe(const std::function<void(float)>& func);
        int subscribe(const std::function<void(Event&)>& func);

        void unsubscribe(long long id);
    private:
        void updateTargets(float delta);
    private:
        unsigned long long id = 0;
        std::unordered_map<int, std::function<void(Event&)>> eventSubscribers;
        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running = true;
        static Application* app;
        float delta;
    };
}