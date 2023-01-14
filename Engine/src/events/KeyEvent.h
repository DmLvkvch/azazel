#pragma once

#include "Event.h"

namespace Azazel
{
    class KeyEvent : public Event
    {
    protected:
        int keycode;

        KeyEvent(int keycode) : keycode(keycode)
        {}
    public:
        int getKeyCode() const
        {
            return this->keycode;
        }
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:    
        KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), repeatCount(repeatCount)
        {
            this->eventCategory = EventCategory::EventCategorykeyboard;
            this->eventType = EventType::KeyPressed;
        }

        static EventType getStaticEventType()
        {
            return EventType::KeyPressed;
        }

        inline int getRepeatCount() const
        {
            return this->repeatCount;
        }

        std::string toString() override
        {
            return "key pressed: " + std::to_string(keycode);
        }
    private:
        int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode)
        {
            this->eventCategory = EventCategory::EventCategorykeyboard;
            this->eventType = EventType::KeyReleased;
        }

        static EventType getStaticEventType()
        {
            return EventType::KeyReleased;
        }

        std::string toString() override
        {
            return "key released: " + std::to_string(keycode);
        }
    };
}