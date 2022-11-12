#pragma once

#include <functional>
#include <string>
#include "events/Event.h"

namespace Azazel
{

    class WindowProps
    {
    public:
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "Azazel Title",
                    unsigned int width = 1280,
                    unsigned int height = 720)
                    : title(title), width(width), height(height)
        {}
    };

    class Window
    {
    public:
        using EventCollbackFn = std::function<void(Event&)>;

        virtual ~Window(){}

        virtual void onUpdate() = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        virtual void setEventCallback(const EventCallbackFb& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        static Window* create(const WindowsProps& props = WindowProps());
    };
}