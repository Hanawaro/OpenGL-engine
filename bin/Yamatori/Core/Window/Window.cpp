#include <ymtpch.hpp>
#include "Window.hpp"

#include <GraphicsAPI/OpenGL/Window/glWindowImpl.hpp>
#include <GraphicsAPI/Vulkan/Window/vkWindowImpl.hpp>

namespace System {
    Window::Window(void) : m_Instance(nullptr) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::Window();
                return;
            case WindowProps::GraphicAPI::DirectX:
                _err << "DirectX not yet supported" << end;
                return;
            case WindowProps::GraphicAPI::Vulkan:
                m_Instance = new VK::Impl::Window();
                return;
            case WindowProps::GraphicAPI::Metal:
                _err << "Metal not yet supported" << end;
                return;
        }
        
        _err << "No such parameter of graphic API" << end;
    }

    Window::~Window(void) {
        delete m_Instance;
    }
}
