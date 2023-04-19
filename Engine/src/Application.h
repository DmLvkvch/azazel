#pragma once

#include "window/Window.h"
#include "LayerStack.h"
#include "camera/Camera.h"
#include <memory>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

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
        std::unique_ptr<Camera> camera;
    };
}