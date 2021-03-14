#include <ymtpch.hpp>
#include "Texture2D.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/Space/2D/Texture/glTexture2DImpl.hpp>

namespace System {
    
    Texture2D::Texture2D(const std::string& path) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Texture2D(path);
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
    
    Texture2D::Texture2D(uint32_t width, uint32_t height) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Texture2D(width, height);
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
    
    Texture2D::Texture2D(void* data, uint32_t width, uint32_t height, size_t size) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Texture2D(data, width, height, size);
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
    
    Texture2D::~Texture2D(void) {
        delete m_Instance;
    }
    
}
