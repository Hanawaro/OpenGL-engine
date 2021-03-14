#pragma once

#include <Yamatori/Core/Renderer/RenderCommand/RenderCommand.hpp>
#include <Yamatori/Core/Renderer/Shader/Shader.hpp>
#include <Yamatori/Space/2D/OrthographicCamera/OrthographicCamera.hpp>
#include <Yamatori/Space/2D/Texture/Texture2D.hpp>

namespace System {
    
    class Renderer2D {
    public:
        Renderer2D(void) = delete;
        Renderer2D(const Renderer2D&) = delete;
        Renderer2D& operator=(const Renderer2D&) = delete;
        
        static void Init(void);
        static void Shutdown(void);
        
        static void Reset(void);
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene(void);

        // draw stuff
        
        // fill quad
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        
        // texture quad
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        
    public:
        struct Info {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };
        
        static Info GetInfo(void);
    private:
        static void SetQuadVertecies(const glm::mat4& transform, size_t vertexIndex, float textureIndex, const glm::vec4& color, float tilingFactor = 1.0f);
    };
    
}
