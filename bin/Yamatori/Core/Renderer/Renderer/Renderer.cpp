#include <ymtpch.hpp>
#include "Renderer.hpp"

namespace System {

    Ref<Renderer::SceneData> Renderer::s_SceneData(new Renderer::SceneData);

    void Renderer::BeginScene(OrthographicCamera& camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        
    }

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader> shader, const glm::mat4& transform) {
        shader->Bind();
        shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetUniformMat4("u_Transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}
