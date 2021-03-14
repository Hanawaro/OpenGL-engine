#include <ymtpch.hpp>
#include "InputAPI.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/InputAPI/glInputAPIImpl.hpp>

namespace System {

    InputAPI::InputAPI(void) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::InputAPI();
                return;
            case WindowProps::GraphicAPI::DirectX:
                _err << "DirectX not yet supported" << end;
                return;
            case WindowProps::GraphicAPI::Vulkan:
                _err << "Vulkan not yet supported" << end;
                return;
            case WindowProps::GraphicAPI::Metal:
                _err << "Metal not yet supported" << end;
                return;
        }
        
        _err << "No such parameter of graphic API" << end;
    }

    InputAPI::~InputAPI(void) {
        delete m_Instance;
    }

}
