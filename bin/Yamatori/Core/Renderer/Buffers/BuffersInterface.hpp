#pragma once

#include "BufferLayout.hpp"

namespace System { namespace Interface {

    class VertexBuffer {
    public:
        VertexBuffer(void) = default;
        virtual ~VertexBuffer(void) = default;
        
        virtual inline void Bind(void) const = 0;
        virtual inline void UnBind(void) const = 0;
        
        virtual void SetData(const void* data, size_t size) = 0;
        
        virtual inline const BufferLayout& GetLayout(void) const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        
        virtual inline uint32_t GetRendererID(void) const = 0;
    };
    
    class IndexBuffer {
    public:
        IndexBuffer(void) = default;
        virtual ~IndexBuffer(void) = default;
        
        virtual inline void Bind(void) const = 0;
        virtual inline void UnBind(void) const = 0;
        
        virtual inline uint32_t GetCount(void) const = 0;
        virtual inline uint32_t GetRendererID(void) const = 0;
    };

} }
