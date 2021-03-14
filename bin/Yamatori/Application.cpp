#include <ymtpch.hpp>
#include "Application.hpp"

#include <Yamatori/Core/Renderer/Renderer/Renderer.hpp>
#include <Yamatori/Space/2D/Renderer/Renderer2D.hpp>

#include <thread>

namespace System {

    Application* Application::s_Instance = nullptr;
    bool Application::m_IsRunning = false;
    
    Application::Application(void) : m_Window(nullptr) {}

    void Application::Init(void) {
        m_IsRunning = true;
        s_Instance = this;
        
        if (WindowProps::configEnable)
            Object::ConfigSetter::SetProperties();
        
        m_Window.reset(new Window());
        m_Window->SetCallBackEvent(std::bind(&Application::HandleEvent, this, std::placeholders::_1));
        
        m_ImGuiLayer = new ImGuiLayer("ImGuiLayer");
        PushOverlay(m_ImGuiLayer);
        
        Renderer2D::Init();
        
        _scs << "Application has been created" << end;
    }

    Application::~Application(void) {
        Renderer2D::Shutdown();
    }

    void Application::Run(void) {
        static float delta = 0;
        
        m_Timer.Restart();
        while (m_IsRunning) {
            float frameTick = 1.0f/WindowProps::frameRate;
            
            delta += m_Timer.DeltaTime().ToSeconds();
            m_Timer.Restart();
            
            if (WindowProps::vSyncEnable || !WindowProps::frameRate) {
                for (auto& layer : m_LayerStack)
                    layer->Update(delta);
                delta = 0;
            } else {
                if (delta < frameTick) {
                    std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameTick - delta)*1000)));
                }
                
                for (auto& layer : m_LayerStack)
                    layer->Update(delta);
                    
                delta = 0;
            }
            
            if (!m_IsMinimized) {
                for (auto& layer : m_LayerStack)
                    layer->Render();
            }
            
            m_ImGuiLayer->Begin();
            for (auto& layer : m_LayerStack)
                layer->ImGuiRender();
            m_ImGuiLayer->End();
            
            m_Window->Update();
        }
    }

    void Application::HandleEvent(Event& event) {
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            if (event.Handled)
                break;
            (*--it)->HandleEvent(event);
        }
        
        m_ImGuiLayer->HandleEvent(event);
        
        EventDispatcher dispatcher(event);
        if (!event.Handled)
            dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));
        
        dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResizeEvent, this, std::placeholders::_1));
        
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& event) {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnKeyPressedEvent(KeyPressedEvent& event) {
        m_IsRunning = false;
        return true;
    }
    
    bool Application::OnWindowResizeEvent(WindowResizeEvent& event) {
        if (event.GetWidth() == 0 && event.GetHeight() == 0) {
            m_IsMinimized = true;
            return false;
        }
        
        Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
        
        m_IsMinimized = false;
        return false;
    }
}
