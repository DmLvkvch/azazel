#pragma once

#include "Event.h"

namespace Azazel
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height)
        : width(width), height(height)
        {
            this->eventCategory = EventCategory::EventCategoryApplication;
            this->eventType = EventType::WindowResize;
        }
        
        static EventType getStaticEventType()
        {
            return EventType::WindowResize;
        }

        inline int getWidth() const
        {
            return width;
        }

        inline int getHeight() const
        {
            return height;
        }

        std::string toString() override
        {
            return "Window resize event. Width: " + std::to_string(width) + "height: " + std::to_string(height);
        }
        
    private:
        int width;
        int height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent()
        {
            this->eventCategory = EventCategory::EventCategoryApplication;
            this->eventType = EventType::WindowClose;
        }
        
        static EventType getStaticEventType()
        {
            return EventType::WindowClose;
        }

        std::string toString()
        {
            return "Window close event.";
        }
    };

    class AppTickEvent : public Event
    {
    
    public:
        AppTickEvent()
        {
            this->eventCategory = EventCategory::EventCategoryApplication;
            this->eventType = EventType::AppTick;
        }

        static EventType getStaticEventType()
        {
            return EventType::AppTick;
        }

        std::string toString()
        {
            return "App tick event.";
        }
    };


    class AppUpdateEvent : public Event
    {
        AppUpdateEvent()
        {
            this->eventCategory = EventCategory::EventCategoryApplication;
            this->eventType = EventType::AppUpdate;
        }

        static EventType getStaticEventType()
        {
            return EventType::AppUpdate;
        }

        std::string toString() override
        {
            return "App update event.";
        }
    };
}