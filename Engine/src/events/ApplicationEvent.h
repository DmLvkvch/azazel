#pragma once

#include "Event.h"

namespace Azazel
{
    class WindowResizeEvent : public Event
    {
    private:
        int width;
        int height;
    public:
        WindowResizeEvent(int width, int height)
        :width(width), height(height)
        {
            this->eventCategory = EventCategory::EventCategoryApplication;
            this->eventType = EventType::WindowResize;
        }
        
        static EventType getStaticEventType()
        {
            return EventType::WindowResize;
        }

        std::string toString()
        {
            return "key pressed: keycode: ";
        }
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
            return "key pressed: keycode: ";
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
            return "key pressed: keycode: ";
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

        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    };
}