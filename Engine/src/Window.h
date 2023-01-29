#pragma once

#include <functional>
#include <string>
#include "events/Event.h"
#include <memory>

namespace Azazel
{

    class WindowProperties
    {
    public:
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProperties(const std::string& title = "Azazel Title",
                    unsigned int width = 1280,
                    unsigned int height = 720)
        : title(title), width(width), height(height) {}
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        Window() {}
        virtual ~Window(){}
        virtual void onUpdate(float delta) = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;
        virtual void* getNativeWindow() = 0;
        static Window* create(const WindowProperties& props = WindowProperties());
    private:
        static Window* window;
    };
}