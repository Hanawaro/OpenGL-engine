#pragma once

#include "BuffersInterface.hpp"
#include <Yamatori/Logger/Logger.hpp>

namespace System {

    class VertexBuffer {
    public:
        VertexBuffer(size_t size);
        VertexBuffer(float* vertices, size_t size);
        ~VertexBuffer(void);
        
        inline void Bind(void) const { m_Instance->Bind(); }
        inline void UnBind(void) const { m_Instance->UnBind(); }
        
        inline void SetData(const void* data, size_t size) { m_Instance->SetData(data, size); }
        
        inline const BufferLayout& GetLayout(void) const { return m_Instance->GetLayout(); }
        inline void SetLayout(const BufferLayout& layout) { m_Instance->SetLayout(layout); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
    private:
        Interface::VertexBuffer* m_Instance;
    };
    
    class IndexBuffer {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer(void);
        
        inline void Bind(void) const { m_Instance->Bind(); }
        inline void UnBind(void) const { m_Instance->UnBind(); };
        
        inline uint32_t GetCount(void) const { return m_Instance->GetCount(); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
    private:
        Interface::IndexBuffer* m_Instance;
    };
    
}
