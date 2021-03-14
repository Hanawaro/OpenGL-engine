#pragma once

#include "WindowInterface.hpp"

namespace System {
    
    class Window {
    public:
        Window(void);
        ~Window(void);
        
        inline void Update(void) { m_Instance->Update(); }
        inline void SetCallBackEvent(std::function<void(Event&)> callback) { m_Instance->SetCallBackEvent(callback); };
        
        inline void ReCreate(void) { m_Instance->ReCreate(); }
        inline void Callback(Event& event) { m_Instance->Callback(event); };
        
        inline std::pair<uint32_t, uint32_t> GetSize(void) const { return m_Instance->GetSize(); }
        inline uint32_t GetWidth(void) const { return m_Instance->GetWidth(); }
        inline uint32_t GetHeight(void) const { return m_Instance->GetHeight(); }
        
        inline bool GetVSync(void) const { return m_Instance->GetVSync(); }
        inline void SetVSync(bool enabled) { m_Instance->SetVSync(enabled); }
        
        inline void* GetNativeWindow(void) const { return m_Instance->GetNativeWindow(); }
    protected:
        Interface::Window* m_Instance;
    };

}
