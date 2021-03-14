#include <ymtpch.hpp>
#include "VertexArray.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/Stuff/VertexArray/glVertexArrayImpl.hpp>

namespace System {

    VertexArray::VertexArray(void) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::VertexArray();
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
    
    VertexArray::~VertexArray(void) {
        delete m_Instance;
    }

}
