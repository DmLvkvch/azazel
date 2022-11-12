#pragma once

#include <string>
#include <functional>
\
namespace Azazel
{
    enum class EventType
    {
        NONE = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MousePressed, MouseReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput       = 1 << 1,
        EventCategorykeyboard    = 1 << 2,
        EventCategoryMouse       = 1 << 3,
        EventCategoryMouseButton = 1 << 4
    };

    class Event
    {
        friend class EventDispatcher;
    public:
        bool handled = false;
    protected:
        EventType eventType;
        EventCategory eventCategory;

    public:
        virtual EventType getEventType()
        {
            return eventType;
        }

        virtual EventCategory getEventCategory()
        {
            return eventCategory;
        }

        virtual int getCategoryFlags()
        {
            return eventCategory;
        }

        bool isInCategory(EventCategory& eventCategory)
        {
            return this->eventCategory & eventCategory;
        }

        virtual std::string toString() = 0;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
        : event(event)
        {
        }

        template<typename T>
        bool dispatch(EventFn<T> func)
        {
            if (event.getEventType() == T::getStaticType())
            {
                event.handled = func(*(T*) &event);
                return true;
            }
            return false;
        }
    private:
        Event& event;    
    };
}