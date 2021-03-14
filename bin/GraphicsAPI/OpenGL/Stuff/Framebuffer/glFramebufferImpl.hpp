#pragma once

#include <Yamatori/Core/Renderer/Framebuffer/FramebufferInterface.hpp>
#include <Yamatori/Logger/Logger.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace System { namespace GL { namespace Impl {
    
    class Framebuffer final : public Interface::Framebuffer {
    public:
        Framebuffer(const Specification specification);
        virtual ~Framebuffer(void);
        
        virtual inline void Bind(void) const override {
            glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
            glViewport(0, 0, m_Specification.Width, m_Specification.Height);
        }
        
        virtual inline void UnBind(void) const override { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
        
        virtual void Resize(uint32_t width, uint32_t height) override {
            m_Specification.Width = width;
            m_Specification.Height = height;

            Invalidate();
        }
        
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
        virtual inline uint32_t GetColorAttachmentRendererID(void) const override { return m_ColorAttachment; }
        virtual inline uint32_t GetDepthAttachmentRendererID(void) const override { return m_DepthAttachment; }
        
        virtual inline const Specification& GetSpecification(void) const override { return m_Specification; }
    private:
        void Invalidate(void);
    private:
        Specification m_Specification;
        uint32_t m_RendererID = 0;
        
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
    };
    
} } }
