#pragma once

#include "Event.hpp"
#include <Yamatori/Core/Window/WindowProps.hpp>

namespace System {

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
        
        inline unsigned int GetWidth(void) const { return m_Width; }
        inline unsigned int GetHeight(void) const { return m_Height; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << WindowProps::width << ", " << WindowProps::height;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::WindowResize; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "WindowResize"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryApplication; }
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent(void) {}
        
        static EventType GetStaticType(void) { return EventType::WindowClose; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "WindowClose"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryApplication; }
    };

    class AppTickEvent : public Event {
    public:
        AppTickEvent(void) {}
        
        static EventType GetStaticType(void) { return EventType::AppTick; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "AppTick"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryApplication; }
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent(void) {}
        
        static EventType GetStaticType(void) { return EventType::AppUpdate; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "AppUpdate"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryApplication; }
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent(void) {}
        
        static EventType GetStaticType(void) { return EventType::AppRender; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "AppRender"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryApplication; }
    };

}
