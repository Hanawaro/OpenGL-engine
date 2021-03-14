#pragma once

#include <glm/glm.hpp>
#include <Yamatori/Core/Core.hpp>
#include <Yamatori/Core/Renderer/VertexArray/VertexArray.hpp>

namespace System { namespace Interface {

    class RendererAPI {
    public:
        RendererAPI(void) = default;
        virtual ~RendererAPI(void) = default;
        
        virtual void Init(void) const = 0;
        
        virtual void SetClearColor(const glm::vec4& color) const = 0;
        virtual void Clear(void) const = 0;
        
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        
        virtual void DrawIndexed(const Ref<System::VertexArray>& vertexArray, uint32_t count = 0) const = 0;
    };

} }
