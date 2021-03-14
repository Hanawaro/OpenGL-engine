#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Yamatori/Core/Event/InputAPI/InputAPIInterface.hpp>

#include <GraphicsAPI/OpenGL/InputAPI/glKeyCodes.hpp>
#include <GraphicsAPI/OpenGL/InputAPI/glMouseButtonCodes.hpp>

namespace System { namespace GL { namespace Impl {

    class InputAPI final : public Interface::InputAPI {
    public:
        InputAPI(void) = default;
        virtual ~InputAPI(void) = default;
    
        virtual bool IsKeyPressed(unsigned int keycode) const override;
        virtual bool IsMouseButtonPressed(unsigned int keycode) const override;
        
        virtual std::pair<float, float> GetMousePosition(void) const override;
        virtual float GetMouseX(void) const override;
        virtual float GetMouseY(void) const override;
    };

} } }
