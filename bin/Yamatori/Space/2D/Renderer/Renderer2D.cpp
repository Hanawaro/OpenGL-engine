#include "Renderer2D.hpp"

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace System {
    
    struct VertexData {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TextureCoord;
        float TextureIndex;
        float TextureTiling;
    };
    
    struct BatchRenderingData {
        static const uint32_t MaxQuads = 10000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndecies = MaxQuads * 6;
        static const uint32_t MaxTexSlots = 16;
        
        Ref<VertexArray> VertexArray;
        Ref<VertexBuffer> VertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> FillColorTexture;
        
        uint32_t IndexCount = 0;
        VertexData* VertexBufferBase = nullptr;
        VertexData* VertexBufferPtr = nullptr;
        
        std::array<Ref<Texture2D>, MaxTexSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;
        
        glm::vec4 QuadVertexPositions[4];
        
        Renderer2D::Info Info;
    };
    
    static BatchRenderingData s_Data;
    
    void Renderer2D::Init(void) {
        RenderCommand::Init();
        
        s_Data.VertexArray.reset(new VertexArray());
        s_Data.VertexBuffer.reset(new VertexBuffer(s_Data.MaxVertices * sizeof(VertexData)));
        
        s_Data.VertexBuffer->SetLayout({
            { "a_Position", ShaderDataType::Float3 },
            { "a_Color", ShaderDataType::Float4,  },
            { "a_TexCoord", ShaderDataType::Float2,  },
            { "a_TexIndex", ShaderDataType::Float,  },
            { "a_TilingFactor", ShaderDataType::Float,  }
        });
        s_Data.VertexArray->SetVertexBuffer(s_Data.VertexBuffer);
        
        s_Data.VertexBufferBase = new VertexData[s_Data.MaxVertices];
        uint32_t *indicies = new uint32_t[s_Data.MaxIndecies];
        
        uint32_t offset = 0;
        for (int i = 0; i < s_Data.MaxIndecies; i += 6) {
            indicies[i + 0] = offset + 0;
            indicies[i + 1] = offset + 1;
            indicies[i + 2] = offset + 2;
            
            indicies[i + 3] = offset + 2;
            indicies[i + 4] = offset + 3;
            indicies[i + 5] = offset + 0;
            
            offset += 4;
        }
        Ref<IndexBuffer> tmpIBO(new IndexBuffer(indicies, s_Data.MaxIndecies));
        s_Data.VertexArray->SetIndexBuffer(tmpIBO);
        delete[] indicies;
        
//        s_Data.FillColorTexture.reset(new Texture2D("assets/Pixel.png"));
        uint32_t fillColor = 0xffffffff;
//        s_Data.FillColorTexture.reset(new Texture2D(&fillColor, 1, 1, sizeof(uint32_t)));
        s_Data.FillColorTexture.reset(new Texture2D(1, 1));
        s_Data.FillColorTexture->SetData(&fillColor, sizeof(fillColor));
        
        glm::ivec1 samplers[s_Data.MaxTexSlots];
        for (uint32_t i = 0; i < s_Data.MaxTexSlots; i++)
            samplers[i].x = i;
        
        s_Data.TextureShader.reset(new Shader("assets/shaders/Texture.glsl"));
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetUniform1iv("u_Textures", samplers, s_Data.MaxTexSlots);
        
        s_Data.TextureSlots[0] = s_Data.FillColorTexture;
        
        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }
    
    void Renderer2D::Shutdown(void) {
        delete[] s_Data.VertexBufferBase;
    }
    
    
    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.IndexCount = 0;
        s_Data.VertexBufferPtr = s_Data.VertexBufferBase;

        s_Data.TextureSlotIndex = 1;
        
        s_Data.Info.DrawCalls = 0;
        s_Data.Info.QuadCount = 0;
    }
    
    void Renderer2D::EndScene(void) {
        
        if (!s_Data.IndexCount)
            return;
        
        long dataSize = (s_Data.VertexBufferPtr - s_Data.VertexBufferBase) * sizeof(VertexData);
        s_Data.VertexBuffer->SetData(s_Data.VertexBufferBase, dataSize);

        s_Data.VertexArray->Bind();
        s_Data.FillColorTexture->Bind();
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
            s_Data.TextureSlots[i]->Bind(i);
        
        RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.IndexCount);
        s_Data.Info.DrawCalls++;
    }

    void Renderer2D::Reset(void) {
        EndScene();

        s_Data.IndexCount = 0;
        s_Data.VertexBufferPtr = s_Data.VertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }
    
    // draw stuff
    
    // fill quad
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        if (s_Data.IndexCount >= BatchRenderingData::MaxIndecies)
            Reset();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                  * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        for (int i = 0; i < 4; i++)
            SetQuadVertecies(transform, i, 0.0f, color);
        
        s_Data.IndexCount += 6;
        s_Data.Info.QuadCount++;
    }
    
    
    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                    * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        for (int i = 0; i < 4; i++)
            SetQuadVertecies(transform, i, 0.0f, color);
        
        s_Data.IndexCount += 6;
        s_Data.Info.QuadCount++;
    }
    
    // texture quad
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
        DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
        
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
        
        if (s_Data.IndexCount >= BatchRenderingData::MaxIndecies)
            Reset();
        
        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
            if (s_Data.TextureSlots[i].get() == texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = (float) s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                  * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        for (int i = 0; i < 4; i++)
            SetQuadVertecies(transform, i, textureIndex, tintColor, tilingFactor);
        
        s_Data.IndexCount += 6;
        s_Data.Info.QuadCount++;
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, texture, rotation, tilingFactor, tintColor);
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        
        if (s_Data.IndexCount >= BatchRenderingData::MaxIndecies)
            Reset();
        
        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
            if (s_Data.TextureSlots[i].get() == texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = (float) s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                    * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        for (int i = 0; i < 4; i++)
            SetQuadVertecies(transform, i, textureIndex, tintColor, tilingFactor);
        
        s_Data.IndexCount += 6;
        s_Data.Info.QuadCount++;
    }
    
    void Renderer2D::SetQuadVertecies(const glm::mat4& transform, size_t vertexIndex, float textureIndex, const glm::vec4& color, float tilingFactor) {
        
        glm::vec2 texCoord(0.0f);
        switch (vertexIndex) {
            case 0:
                texCoord = { 0.0f, 0.0f };
                break;
            case 1:
                texCoord = { 1.0f, 0.0f };
                break;
            case 2:
                texCoord = { 1.0f, 1.0f };
                break;
            case 3:
                texCoord = { 0.0f, 1.0f };
                break;
            default:
                break;
        }
        
        s_Data.VertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[vertexIndex];
        s_Data.VertexBufferPtr->Color = color;
        s_Data.VertexBufferPtr->TextureCoord = texCoord;
        s_Data.VertexBufferPtr->TextureIndex = textureIndex;
        s_Data.VertexBufferPtr->TextureTiling = tilingFactor;
        s_Data.VertexBufferPtr++;
    }
    
    Renderer2D::Info Renderer2D::GetInfo(void) { return s_Data.Info; }
}
