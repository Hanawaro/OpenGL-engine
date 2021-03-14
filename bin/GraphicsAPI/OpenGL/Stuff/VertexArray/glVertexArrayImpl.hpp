#pragma once

#include <Yamatori/Core/Renderer/VertexArray/VertexArrayInterface.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace System { namespace GL { namespace Impl {

    class VertexArray final : public Interface::VertexArray {
    public:
        VertexArray(void);
        virtual ~VertexArray(void);
        
        virtual inline void Bind(void) const override { glBindVertexArray(m_RendererID); }
        virtual inline void UnBind(void) const override { glBindVertexArray(0); }
        
        virtual void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        
        virtual inline const Ref<VertexBuffer>& GetVertexBuffer(void) const override { return m_VertexBuffer; }
        virtual inline const Ref<IndexBuffer>& GetIndexBuffer(void) const override { return m_IndexBuffer; }
        
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
    private:
        uint32_t m_RendererID;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };

} } }
