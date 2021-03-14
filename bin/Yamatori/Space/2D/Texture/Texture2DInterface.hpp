#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System { namespace Interface {
   
    class Texture2D {
    public:
        Texture2D(void) = default;
        virtual ~Texture2D(void) = default;
        
        virtual void SetTexture(const std::string& path) = 0;
        
        virtual void SetData(void* data, size_t size) = 0;
        
        virtual void Bind(int slot = 0) = 0;
        virtual void UnBind(void) = 0;
        
        virtual inline std::pair<uint32_t, uint32_t> GetSize(void) const = 0;
        virtual inline uint32_t GetWidth(void) const = 0;
        virtual inline uint32_t GetHeight(void) const = 0;
        
        virtual inline uint32_t GetRendererID(void) const = 0;
    };
    
} }
