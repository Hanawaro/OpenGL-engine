#pragma once

#include <Yamatori/Core/Renderer/RendererAPI/RendererAPIInterface.hpp>

namespace System { namespace GL { namespace Impl {

    class RendererAPI final : public Interface::RendererAPI {
    public:
        RendererAPI(void) = default;
        virtual ~RendererAPI(void) = default;
        
        virtual void Init(void) const override;
        
        virtual void SetClearColor(const glm::vec4& color) const override;
        virtual void Clear(void) const override;
        
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) const override;
    };

} } }
