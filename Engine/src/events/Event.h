#pragma once

#include <string>
#include <functional>
#include <unordered_map>

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

    template<typename R, typename ... TArgs>
    class EventDispatcher
    {
        using EventCallback = std::function<R(TArgs...)>;
        using CallbackID = unsigned long long;
    public:    

        CallbackID addListener(const EventCallback& callback)
        {
            callbacks[++id] = callback;
            return id;
        }

        void removeListener(CallbackID id)
        {
            if (callbacks.size() > 0)
            {
                callbacks.erase(id);
            }
        }

        void dispatch(const TArgs& ... t)
        {
            for (const auto& [id, handler] : callbacks)
            {
                handler(t...);
            }
        }

        void clear()
        {
            callbacks.clear();
        }
    private:
        inline static unsigned long long id = 0;
        std::unordered_map<CallbackID, EventCallback> callbacks;
    };
}