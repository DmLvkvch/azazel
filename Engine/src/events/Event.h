#pragma once

#include <string>
#include <functional>

enum class EventType
{
    NONE = 0,
    KeyPressed, KeyReleased,
    MousePressed, MouseReleased, MouseMoved, MouseScrolled
};