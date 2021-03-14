#pragma once

#include <Yamatori/Core/Renderer/Buffers/Buffers.hpp>
#include <Yamatori/Core/Core.hpp>

namespace System { namespace Interface {

    class VertexArray {
    public:
        VertexArray(void) = default;
        virtual ~VertexArray(void) = default;
        
        virtual inline void Bind(void) const = 0;
        virtual inline void UnBind(void) const = 0;
        
        virtual void SetVertexBuffer(const Ref<System::VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<System::IndexBuffer>& indexBuffer) = 0;
        
        virtual inline const Ref<System::VertexBuffer>& GetVertexBuffer(void) const = 0;
        virtual inline const Ref<System::IndexBuffer>& GetIndexBuffer(void) const = 0;
        
        virtual inline uint32_t GetRendererID(void) const = 0;
    };

} }
