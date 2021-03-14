#pragma once

#include <Yamatori/Space/2D/Texture/Texture2DInterface.hpp>

namespace System { namespace GL { namespace Impl {
    
    class Texture2D final : public Interface::Texture2D {
    public:
        Texture2D(uint32_t width, uint32_t height);
        Texture2D(const std::string& path);
        Texture2D(void* data, uint32_t width, uint32_t height, size_t size);
        virtual ~Texture2D(void) = default;
        
        virtual void SetTexture(const std::string& path) override;
        virtual void SetData(void* data, size_t size) override;
        
        virtual void Bind(int slot = 0) override;
        virtual void UnBind(void) override;
        
        virtual inline std::pair<uint32_t, uint32_t> GetSize(void) const override { return m_Size; }
        virtual inline uint32_t GetWidth(void) const override { return m_Size.second; }
        virtual inline uint32_t GetHeight(void) const override { return m_Size.first; }
        
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
    private:
        std::string m_Path;
        std::pair<uint32_t, uint32_t> m_Size;
        uint32_t m_RendererID;
    };
    
} } }
