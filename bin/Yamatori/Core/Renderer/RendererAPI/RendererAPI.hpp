#pragma once

#include "RendererAPIInterface.hpp"

namespace System {

class RendererAPI {
public:
    RendererAPI(void);
    virtual ~RendererAPI(void);
    
    inline void Init(void) const { m_Instance->Init(); }
    
    inline void SetClearColor(const glm::vec4& color) const { m_Instance->SetClearColor(color); }
    inline void Clear(void) const { m_Instance->Clear(); }
    
    inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const { m_Instance->SetViewport(x, y, width, height); }
    
    inline void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) const { m_Instance->DrawIndexed(vertexArray, count); }
    
private:
    Interface::RendererAPI* m_Instance;
};

}
