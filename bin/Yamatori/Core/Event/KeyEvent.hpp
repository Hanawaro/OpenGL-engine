#pragma once

#include "Event.hpp"

namespace System {

    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : m_KeyCode(keyCode), m_RepeatCount(repeatCount) {}
        
        inline int GetKeyCode(void) const { return m_KeyCode; }
        inline int GetRepeatCount(void) const { return m_RepeatCount; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << ", " << m_RepeatCount;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::KeyPressed; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "KeyPressed"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryKeyboard | EventCategoryInput; }
    private:
        int m_KeyCode;
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(int keyCode) : m_KeyCode(keyCode) {}
        
        inline int GetKeyCode(void) const { return m_KeyCode; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::KeyReleased; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "KeyReleased"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryKeyboard | EventCategoryInput; }
    private:
        int m_KeyCode;
    };

    class KeyTypedEvent : public Event {
    public:
        KeyTypedEvent(int keyCode) : m_KeyCode(keyCode) {}
        
        inline int GetKeyCode(void) const { return m_KeyCode; }
        
        virtual operator std::string() override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }
        
        static EventType GetStaticType(void) { return EventType::KeyTyped; }
        virtual EventType GetEventType(void) const override { return GetStaticType(); }
        virtual const char* GetName(void) const override { return "KeyTyped"; }
        virtual int GetCategoryFlags(void) const override { return EventCategoryKeyboard | EventCategoryInput; }
    private:
        int m_KeyCode;
    };

}
