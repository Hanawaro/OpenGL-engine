#include <ymtpch.hpp>
#include "ImGuiLayer.hpp"

#include <GraphicsAPI/OpenGL/ImGui/glfImGuiLayerImpl.hpp>

namespace System {

    ImGuiLayer::ImGuiLayer(const std::string& debugName) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                m_Instance = new GL::Impl::ImGuiLayer(debugName);
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
    
    ImGuiLayer::~ImGuiLayer(void) {
        delete m_Instance;
    }

}
