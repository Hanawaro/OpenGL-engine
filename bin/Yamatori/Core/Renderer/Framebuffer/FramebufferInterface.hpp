#pragma once

#include "FramebufferSpecification.hpp"

namespace System { namespace Interface {
    
    class Framebuffer {
    public:
        Framebuffer(void) = default;
        virtual ~Framebuffer(void) = default;
        
        virtual inline void Bind(void) const = 0;
        virtual inline void UnBind(void) const = 0;
        
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual inline uint32_t GetRendererID(void) const = 0;
        virtual inline uint32_t GetColorAttachmentRendererID(void) const = 0;
        virtual inline uint32_t GetDepthAttachmentRendererID(void) const = 0;
        
        virtual inline const Specification& GetSpecification(void) const = 0;
    };
    
} }
