#pragma once

#include <Yamatori/Core/Core.hpp>
#include <Yamatori/Core/Renderer/RendererAPI/RendererAPI.hpp>

namespace System {

    class RenderCommand {
    public:
        RenderCommand(void) = delete;
        RenderCommand(const RenderCommand&) = delete;
        RenderCommand& operator=(const RenderCommand&) = delete;
        
        static inline void Init(void) { m_RendererAPI->Init(); }
        
        static inline void SetClearColor(const glm::vec4& color) { m_RendererAPI->SetClearColor(color); }
        static inline void Clear(void) { m_RendererAPI->Clear(); }
        
        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { m_RendererAPI->SetViewport(x, y, width, height); }
        
        static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) { m_RendererAPI->DrawIndexed(vertexArray, count); }
        
        static inline RendererAPI* GetRendererAPI(void) { return m_RendererAPI.get(); }
    private:
        static Ref<RendererAPI> m_RendererAPI;
    };

}
