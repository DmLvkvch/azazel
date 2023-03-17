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
        unsigned long long subscribe(const std::function<void(Event&)>& func);
        unsigned long long subscribe(const std::function<void(float)>& func);

        void unsubscribe(long long id);

    private:
        void updateTargets(float delta);
    private:
        unsigned long long id = 0;
        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running = true;
        static Application* app;
        float delta;
        EventDispatcher<void, Event&> eventSubscribers;
        EventDispatcher<void , float> updateSubscribers;
    };
}