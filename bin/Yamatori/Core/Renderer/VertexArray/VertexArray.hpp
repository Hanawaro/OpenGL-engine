#pragma once

#include "VertexArrayInterface.hpp"

namespace System {

    class VertexArray {
    public:
        VertexArray(void);
        ~VertexArray(void);
        
        void Bind(void) const { m_Instance->Bind(); };
        void UnBind(void) const { m_Instance->UnBind(); }
        
        void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) { m_Instance->SetVertexBuffer(vertexBuffer); }
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) { m_Instance->SetIndexBuffer(indexBuffer); }
        
        const Ref<VertexBuffer>& GetVertexBuffer(void) const { return m_Instance->GetVertexBuffer(); }
        const Ref<IndexBuffer>& GetIndexBuffer(void) const { return m_Instance->GetIndexBuffer(); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
    private:
        Interface::VertexArray* m_Instance;
    };

}
