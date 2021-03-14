#include <ymtpch.hpp>
#include "glToBaseTypeImpl.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace System { namespace GL { namespace Impl {

    uint32_t ToBaseType(const ShaderDataType& data) {
        switch (data)
        {
            case ShaderDataType::None:
                return NULL;
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
        }

        return 0;
    }

} } }
