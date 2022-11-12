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
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:    
        KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), repeatCount(repeatCount)
        {}

        static EventType getStaticEventType()
        {
            return EventType::KeyPressed;
        }

        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    private:
        int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode)
        {}

        static EventType getStaticEventType()
        {
            return EventType::KeyReleased;
        }

        std::string toString()
        {
            return "key pressed: keycode: ";
        }
    };
}