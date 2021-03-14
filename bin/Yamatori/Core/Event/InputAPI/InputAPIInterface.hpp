#pragma once

#include <GraphicsAPI/OpenGL/InputAPI/glKeyCodes.hpp>
#include <GraphicsAPI/OpenGL/InputAPI/glMouseButtonCodes.hpp>

namespace System { namespace Interface {

    class InputAPI {
    public:
        InputAPI(void) = default;
        virtual ~InputAPI(void) = default;
        
        virtual bool IsKeyPressed(unsigned int keycode) const = 0;
        virtual bool IsMouseButtonPressed(unsigned int keycode) const = 0;
        
        virtual std::pair<float, float> GetMousePosition(void) const = 0;
        virtual float GetMouseX(void) const = 0;
        virtual float GetMouseY(void) const = 0;
    };

} }
