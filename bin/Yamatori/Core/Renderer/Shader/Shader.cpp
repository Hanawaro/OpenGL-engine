#include <ymtpch.hpp>
#include "Shader.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/Stuff/Shader/glShaderImpl.hpp>

namespace System {

    Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Shader(name, vertexSrc, fragmentSrc);
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
    
    Shader::Shader(const std::string& filePath) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Shader(filePath);
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

    Shader::~Shader(void) {
        delete m_Instance;
    }

}
