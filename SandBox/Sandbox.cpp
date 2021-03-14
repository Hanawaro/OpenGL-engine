#include <Yamatori.hpp>
#include <EntryPoint.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Yamatori/Space/2D/Texture/Texture2D.hpp>
#include <Yamatori/Space/2D/Renderer/Renderer2D.hpp>

using namespace System;

class SandBoxLayer final : public System::Layer {
public:
    SandBoxLayer(float aspectRatio) : m_CameraController(aspectRatio, true) {}
    virtual ~SandBoxLayer(void) = default;
    
    virtual void Attach(void) override {
        m_TextureBG.reset(new Texture2D("Assets/Checkerboard.png"));
        m_Texture.reset(new Texture2D("Assets/ue.png"));
        m_Inst.reset(new Texture2D("Assets/Inst.png"));
    }
    
    virtual void Detach(void) override {}
    
    virtual void Update(float delta = 1.0f) override {
        m_CameraController.OnUpdate(delta);
        m_Rotation += delta * 10;
        if (m_Rotation >= 360) m_Rotation -= 360;
    }
    
    virtual void Render(void) override {
        RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1.0});
        RenderCommand::Clear();
        
        Renderer2D::BeginScene(m_CameraController.get());
        
        float range = 0;
        
        for (float i = -range; i < range; i+=0.2f)
            for (float j = -range; j < range; j+=0.2f)
                Renderer2D::DrawQuad({ i, j }, { 0.15f, 0.15f }, { 0.2, 0.3, 0.5, 1.0f });
        
        Renderer2D::DrawQuad({ -0.6f, -0.45f }, { 1.0, 1.0 }, { 0.4f, 0.4f, 0.4f, 1.0f });
        Renderer2D::DrawQuad({ -0.6f, -0.45f }, { 1.0f, 1.0f }, m_Texture, 10.0f);
        
        Renderer2D::DrawQuad({ 0.6f, -0.45f }, { 1.0f, 1.0f }, m_TextureBG, 10.0f);
        Renderer2D::DrawQuad({ 0.6f, -0.45f }, { 1.0f, 1.0f }, m_Texture);
        
        Renderer2D::DrawQuad({ 0.0, 0.5f }, { 0.8f, 0.8f }, m_TextureBG);
        Renderer2D::DrawRotatedQuad({ 0.0, 0.5f }, { 0.6f, 0.6f }, m_Inst, m_Rotation, 1.0f, {0.7f, 1.0f, 1.0f, 1.0f});
        
        Renderer2D::EndScene();
    }
    
    virtual void ImGuiRender(void) override {
        
        ImGui::SetNextWindowSize({170, 100});
        ImGui::SetNextWindowPos({151, 74});
        
        ImGui::Begin("Info rendering");
        
        ImGui::Text("Draw calls:   %d", Renderer2D::GetInfo().DrawCalls);
        ImGui::Text("Quad count:   %d", Renderer2D::GetInfo().QuadCount);
        ImGui::Text("Vertex count: %d", Renderer2D::GetInfo().GetTotalVertexCount());
        ImGui::Text("Index count:  %d", Renderer2D::GetInfo().GetTotalIndexCount());
        
        ImGui::End();
    }
    
    virtual void HandleEvent(System::Event& event) override {
        if(Input::IsKeyPressed(GL::Key::Space)) {
            Application::EndApplication();
            return;
        }
        m_CameraController.OnEvent(event);
    };
    
private:
    Ref<Texture2D> m_TextureBG;
    Ref<Texture2D> m_Texture;
    Ref<Texture2D> m_Inst;

    float m_Rotation = 0;
    
    OrthographicCameraController m_CameraController;
};

class SandBoxApp : public System::Application {
public:
    SandBoxApp(void) = default;
    virtual ~SandBoxApp(void) = default;
    
    void InitImpl(void) override {
        float aspectRatio = (float) WindowProps::width/WindowProps::height;
        PushLayer(new SandBoxLayer(aspectRatio));
    }
    
    void SetWindowProps(void) const override {
        WindowProps::title            = "Sandbox application";
        WindowProps::mode             = WindowProps::Mode::MaximizedWindow;
        WindowProps::graphicAPI       = WindowProps::GraphicAPI::OpenGL;
        WindowProps::width            = 1960;
        WindowProps::height           = 1280;
        WindowProps::fullscreenWidth  = 800;
        WindowProps::fullscreenHeight = 600;
        WindowProps::frameRate        = 120;
        
        WindowProps::vSyncEnable   = true;
        WindowProps::resizeEnable  = true;
        WindowProps::borderEnable  = true;
        
        WindowProps::configEnable = false;
    }
    
    void SetLoggerProps(void) const override {
        System::log.SetGlobaleMode( System::Logger::GlobalMode::AllStuff);
        System::log.SetLocaleMode( System::Logger::LocaleMode::All);
    }
};

System::Application* System::CreateApplication(void) {
    return new SandBoxApp();
}
