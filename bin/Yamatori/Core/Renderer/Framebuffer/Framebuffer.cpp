#include "Framebuffer.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/Stuff/Framebuffer/glFramebufferImpl.hpp>

namespace System {

    Framebuffer::Framebuffer(const Specification& specification) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Framebuffer(specification);
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
    
    Framebuffer::~Framebuffer(void) {
        delete m_Instance;
    }
    
};
