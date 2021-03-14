#pragma once

#include "InputAPIInterface.hpp"

namespace System {

    using KeyCode   = uint16_t;
    using MouseCode = uint16_t;

    class InputAPI {
    public:
        InputAPI(void);
        virtual ~InputAPI(void);
        
        inline bool IsKeyPressed(unsigned int keycode) const { return m_Instance->IsKeyPressed(keycode); };
        inline bool IsMouseButtonPressed(unsigned int button) const { return m_Instance->IsMouseButtonPressed(button); }
        
        inline std::pair<float, float> GetMousePosition(void) const { return m_Instance->GetMousePosition(); }
        inline float GetMouseX(void) const { return m_Instance->GetMouseX(); }
        inline float GetMouseY(void) const { return m_Instance->GetMouseY(); }
    private:
        Interface::InputAPI* m_Instance;
    };

}
