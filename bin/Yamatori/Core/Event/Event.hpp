#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    
    enum EventCategory {
        None = 0,
        EventCategoryApplication    = 1 << 0,
        EventCategoryInput          = 1 << 1,
        EventCategoryKeyboard       = 1 << 2,
        EventCategoryMouse          = 1 << 3,
        EventCategoryMouseButton    = 1 << 4
    };
    
    class Event {
    public:
        bool Handled = false;
    public:
        virtual EventType GetEventType(void) const = 0;
        virtual int GetCategoryFlags(void) const = 0;
        virtual const char* GetName(void) const = 0;
//        virtual std::string ToString(void) const { return GetName(); }
        virtual operator std::string() { return GetName(); }
        
        inline bool IsInCatagory(EventCategory category) {
            return category & GetCategoryFlags();
        }
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T>
        bool dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

}
