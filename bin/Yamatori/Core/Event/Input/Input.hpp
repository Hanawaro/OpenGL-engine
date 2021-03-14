#pragma once

#include <Yamatori/Core/Event/AppEvent.hpp>
#include <Yamatori/Core/Event/KeyEvent.hpp>
#include <Yamatori/Core/Event/MouseEvent.hpp>

#include <Yamatori/Core/Core.hpp>
#include <Yamatori/Core/Event/InputAPI/InputAPI.hpp>

namespace System {

    using KeyCode   = uint16_t;
    using MouseCode = uint16_t;

    class Input {
    public:
        Input(void) = delete;
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;
        
        virtual ~Input(void) = default;
        
        static inline bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressed(keycode); };
        static inline bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressed(button); }
        
        static inline std::pair<float, float> GetMousePosition(void) { return s_Instance->GetMousePosition(); }
        static inline float GetMouseX(void) { return s_Instance->GetMouseX(); }
        static inline float GetMouseY(void) { return s_Instance->GetMouseY(); }
    protected:
        static Ref<InputAPI> s_Instance;
    };

}
