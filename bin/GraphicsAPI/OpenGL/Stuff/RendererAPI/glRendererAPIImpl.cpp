#include <ymtpch.hpp>
#include "glRendererAPIImpl.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Yamatori/Core/Core.hpp>

namespace System { namespace GL { namespace Impl {

    void RendererAPI::Init(void) const {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    void RendererAPI::SetClearColor(const glm::vec4& color) const {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RendererAPI::Clear(void) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) const {
        if (count)
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        else
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width * s_Scale, height * s_Scale);
    }

} } }
