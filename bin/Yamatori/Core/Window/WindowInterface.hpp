#pragma once

#include "WindowProps.hpp"
#include <Yamatori/Core/Event/Input/Input.hpp>

namespace System { namespace Interface {

    class Window {
    public:
        Window(void) = default;
        virtual ~Window(void) = default;
        
        virtual void Update(void) = 0;
        virtual inline void SetCallBackEvent(std::function<void(Event&)> callback) = 0;
        
        virtual void ReCreate(void) = 0;
        virtual void Callback(Event& event) const = 0;
        
        virtual inline std::pair<uint32_t, uint32_t> GetSize(void) const = 0;
        virtual inline uint32_t GetWidth(void) const = 0;
        virtual inline uint32_t GetHeight(void) const = 0;
        
        virtual inline bool GetVSync(void) const = 0;
        virtual void SetVSync(bool enabled) = 0;
        
        virtual inline void* GetNativeWindow(void) const = 0;
    };


} }
