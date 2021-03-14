#pragma once

#include <Yamatori/Core/Renderer/Buffers/BuffersInterface.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace System { namespace GL { namespace Impl {

    class VertexBuffer final : public Interface::VertexBuffer {
    public:
        VertexBuffer(size_t size);
        VertexBuffer(float* vertices, size_t size);
        virtual ~VertexBuffer(void);
        
        virtual inline void Bind(void) const override { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
        virtual inline void UnBind(void) const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        
        virtual void SetData(const void* data, size_t size) override;
        
        virtual inline const BufferLayout& GetLayout(void) const override { return m_Buffer; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Buffer = layout; }
        
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Buffer;
    };

    class IndexBuffer final : public Interface::IndexBuffer {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~IndexBuffer(void);
        
        virtual inline void Bind(void) const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
        virtual inline void UnBind(void) const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        
        virtual inline uint32_t GetCount(void) const override { return m_Count; }
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

} } }
