#include <ymtpch.hpp>
#include "glVertexArrayImpl.hpp"

namespace System { namespace GL { namespace Impl {
    
    VertexArray::VertexArray(void) { glGenVertexArrays(1, &m_RendererID); }

    VertexArray::~VertexArray(void) { glDeleteVertexArrays(1, &m_RendererID); }
    
    void VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        if (!vertexBuffer->GetLayout().GetElements().size()) {
            _err << "Vertex Buffer has no layout!" << end;
            return;
        }
        
        this->Bind();
        vertexBuffer->Bind();

        m_VertexBuffer = vertexBuffer;
        
        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataType::ToBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*) element.Offset);
            index++;
        }
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        this->Bind();
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

} } }
