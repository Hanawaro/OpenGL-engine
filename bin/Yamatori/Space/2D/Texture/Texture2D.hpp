#pragma once

#include "Texture2DInterface.hpp"

namespace System {
    
    class Texture2D {
    public:
        Texture2D(uint32_t width, uint32_t height);
        Texture2D(const std::string& path);
        Texture2D(void* data, uint32_t width, uint32_t height, size_t size);
        virtual ~Texture2D(void);
        
        inline void Bind(int slot = 0) { return m_Instance->Bind(slot); }
        inline void UnBind(void) { m_Instance->UnBind(); }
        
        inline void SetData(void* data, size_t size) { m_Instance->SetData(data, size); }
        
        inline std::pair<uint32_t, uint32_t> GetSize(void) const { return m_Instance->GetSize(); }
        inline uint32_t GetWidth(void) const { return m_Instance->GetWidth(); }
        inline uint32_t GetHeight(void) const { return m_Instance->GetHeight(); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
    private:
        Interface::Texture2D* m_Instance;
    };
    
}
