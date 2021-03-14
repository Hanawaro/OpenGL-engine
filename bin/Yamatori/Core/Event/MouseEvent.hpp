#pragma once

#include "Event.hpp"

namespace System {

    class MouseButtonPressedEvent : public Event {
    public:
        MouseButtonPressedEvent(int keyCode) : m_keyCode(keyCode) {};
        
        inline int GetKeyCode(void) const { return m_keyCode; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_keyCode;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::MouseButtonPressed; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "MouseButtonPressed"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryMouse | EventCategoryInput; }
    private:
        int m_keyCode;
    };

    class MouseButtonReleasedEvent : public Event {
    public:
        MouseButtonReleasedEvent(int keyCode) : m_keyCode(keyCode) {};
        
        inline int GetKeyCode(void) const { return m_keyCode; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_keyCode;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::MouseButtonReleased; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "MouseButtonReleased"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryMouse | EventCategoryInput; }
    private:
        int m_keyCode;
    };

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
        
        inline float GetX(void) const { return m_MouseX; }
        inline float GetY(void) const { return m_MouseY; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::MouseMoved; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "MouseMoved"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryMouse | EventCategoryInput; }
    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
        
        inline float GetXOffset(void) const { return m_XOffset; }
        inline float GetYOffset(void) const { return m_YOffset; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::MouseScrolled; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "MouseScrolled"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryMouse | EventCategoryInput; }
    private:
        float m_XOffset, m_YOffset;
    };

}
