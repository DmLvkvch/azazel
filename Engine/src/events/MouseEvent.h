#pragma once

#include "Event.h"

namespace Azazel
{
    class MouseMovedEvent : public Event
    {
    public:

        MouseMovedEvent(float x, float y)
        : mouseX(x), mouseY(y)
        {
            this->eventCategory = EventCategory::EventCategoryMouse;
            this->eventType = EventType::MouseMoved;
        }

        const inline float getX() const
        {
            return mouseX;
        }

        const inline float getY() const
        {
            return mouseY;
        }

        static EventType getStaticEventType()
        {
            return EventType::MouseMoved;
        }
        
        std::string toString()
        {
            return "Mouse moved: " + std::to_string(getX()) + "y: " + std::to_string(getY());
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
        {
            this->eventCategory = EventCategory::EventCategoryMouse;
            this->eventType = EventType::MouseScrolled;
        }
        
        static EventType getStaticEventType()
        {
            return EventType::MouseScrolled;
        }

        std::string toString()
        {
            return "Mouse scroll: " + std::to_string(offsetX) + "offsetY: " + std::to_string(offsetY);
        }

        const inline float getX() const
        {
            return offsetX;
        }

        const inline float getY() const
        {
            return offsetY;
        }
    private:
        float offsetX;
        float offsetY;    
    };

    class MouseButtonEvent : public Event
    {
    public:
        int getButton() const
        {
            return button;
        }
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
        {
            this->eventCategory = EventCategory::EventCategoryMouseButton;
            this->eventType = EventType::MousePressed;
        }
        
        static EventType getStaticEventType()
        {
            return EventType::MousePressed;
        }
        
        std::string toString()
        {
            return "Mouse button pressed: " + std::to_string(button);
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button)
        {
            this->eventCategory = EventCategory::EventCategoryMouseButton;
            this->eventType = EventType::MouseReleased;
        }

        static EventType getStaticEventType()
        {
            return EventType::MouseReleased;
        }
        
        std::string toString()
        {
            return "Mouse button released: " + std::to_string(button);
        }
    };
}