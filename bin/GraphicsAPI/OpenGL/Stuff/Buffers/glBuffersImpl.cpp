#include <ymtpch.hpp>
#include "glBuffersImpl.hpp"

namespace System { namespace GL { namespace Impl {

    VertexBuffer::VertexBuffer(size_t size) : m_RendererID(0) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }
    
    VertexBuffer::VertexBuffer(float* vertices, size_t size) : m_RendererID(0) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer(void) {
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::SetData(const void* data, size_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        
    }

    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_RendererID(0), m_Count(count) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer(void) {
        glDeleteBuffers(1, &m_RendererID);
    }

} } }
