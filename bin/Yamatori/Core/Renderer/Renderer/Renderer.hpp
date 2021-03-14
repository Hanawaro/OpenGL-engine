#pragma once

#include <Yamatori/Core/Renderer/RenderCommand/RenderCommand.hpp>
#include <Yamatori/Core/Renderer/Shader/Shader.hpp>
#include <Yamatori/Space/2D/OrthographicCamera/OrthographicCameraController.hpp>

namespace System {

    class Renderer {
    public:
        Renderer(void) = delete;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        
        static inline void Init(void) { RenderCommand::Init(); }
        
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void OnWindowResize(uint32_t width, uint32_t height) { RenderCommand::SetViewport(0, 0, width, height); }
        
        static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static Ref<SceneData> s_SceneData;
    };

}
