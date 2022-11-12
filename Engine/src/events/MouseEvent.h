#pragma once

#include "Event.h"

namespace Azazel
{
    class MouseMovedEvent : public Event
    {
    public:

        MouseMovedEvent(float x, float y)
        : mouseX(x), mouseY(y)
        {}

        float getX()
        {
            return mouseX;
        }

        float getY()
        {
            return mouseY;
        }

        static EventType getStaticEventType()
        {
            return EventType::MouseMoved;
        }
        
        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    private:
        float mouseX;
        float mouseY;
    };

    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float offsetX, float offsetY)
        : offsetX(offsetX), offsetY(offsetY)
        {}
        
        static EventType getStaticEventType()
        {
            return EventType::MouseScrolled;
        }

        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    private:
        float offsetX;
        float offsetY;    
    };

    class MouseButtonEvent : public Event
    {
    protected:
        MouseButtonEvent(int button) : button(button)
        {}
        
        int button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button)
        {}
        
        static EventType getStaticEventType()
        {
            return EventType::MousePressed;
        }
        
        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button)
        {}

        static EventType getStaticEventType()
        {
            return EventType::MouseReleased;
        }
        
        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    };
}