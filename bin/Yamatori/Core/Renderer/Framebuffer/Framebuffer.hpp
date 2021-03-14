#pragma once

#include "FramebufferInterface.hpp"
#include <Yamatori/Core/Core.hpp>

namespace System {
    
    class Framebuffer {
    public:
        Framebuffer(const Specification& specification);
        ~Framebuffer(void);
        
        inline void Bind(void) const { m_Instance->Bind(); }
        inline void UnBind(void) const { m_Instance->UnBind(); }
        
        inline void Resize(uint32_t width, uint32_t height) const { m_Instance->Resize(width, height); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
        inline uint32_t GetColorAttachmentRendererID(void) const { return m_Instance->GetColorAttachmentRendererID(); }
        inline uint32_t GetDepthAttachmentRendererID(void) const { return m_Instance->GetDepthAttachmentRendererID(); }
        
        inline const Specification& GetSpecification(void) const { return m_Instance->GetSpecification(); }
    private:
        Interface::Framebuffer* m_Instance;
    };
    
}
