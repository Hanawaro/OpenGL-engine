#include <ymtpch.hpp>
#include "BufferLayout.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <GraphicsAPI/OpenGL/Stuff/glToBaseTypeImpl.hpp>

namespace System {

    uint32_t ShaderDataType::ToBaseType(const ShaderDataType& data) {
        switch (WindowProps::graphicAPI) {
            case WindowProps::GraphicAPI::OpenGL:
                return GL::Impl::ToBaseType(data);
            case WindowProps::GraphicAPI::DirectX:
                _err << "DirectX not yet supported" << end;
                return 0;
            case WindowProps::GraphicAPI::Vulkan:
                _err << "Vulkan not yet supported" << end;
                return 0;
            case WindowProps::GraphicAPI::Metal:
                _err << "Metal not yet supported" << end;
                return 0;
        }
        
        _err << "No such parameter of graphic API" << end;
        return 0;
    }
    
    uint32_t ShaderDataType::GetSize(const ShaderDataType& data) {
        switch (data) {
            case None:
                return NULL;
            case Float:
                return sizeof(float);
            case Float2:
                return sizeof(float)*2;
            case Float3:
                return sizeof(float)*3;
            case Float4:
                return sizeof(float)*4;
            case Int:
                return sizeof(int);
            case Int2:
                return sizeof(int)*2;
            case Int3:
                return sizeof(int)*3;
            case Int4:
                return sizeof(int)*4;
            case Bool:
                return sizeof(bool);
            case Mat3:
                return sizeof(float)*3;
            case Mat4:
                return sizeof(float)*4;
        }
        _wrn << "No such data type" << end;
        return NULL;
    }

    uint32_t BufferElement::GetComponentCount(void) const {
        switch (Type) {
            case ShaderDataType::None:
                return 0;
            case ShaderDataType::Float:
            case ShaderDataType::Int:
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::Float2:
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Float3:
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Float4:
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Mat3:
                return 3*3;
            case ShaderDataType::Mat4:
                return 4*4;
        }
        
        _wrn << "No such data type" << end;
        return 0;
    }

}
