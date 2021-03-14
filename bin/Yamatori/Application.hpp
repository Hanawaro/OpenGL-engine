#pragma once

#include <Yamatori/Core/Core.hpp>

#include <Yamatori/Logger/Logger.hpp>
#include <Yamatori/Objects/ConfigSetter/ConfigSetter.hpp>

#include <Yamatori/Core/Window/Window.hpp>
#include <Yamatori/Core/Window/WindowProps.hpp>

#include <Yamatori/Core/Event/Input/Input.hpp>

#include <Yamatori/Core/Layers/LayerStack.hpp>
#include <Yamatori/ImGui/ImGuiLayer.hpp>

#include <Yamatori/Objects/Timer/Timer.hpp>

namespace System {

    class Application {
    public:
        Application(void);
        virtual ~Application(void);
        
        void Init(void);
        virtual void InitImpl(void) = 0;
        
        void Run(void);
        void HandleEvent(Event& event);
        
        inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); };
        inline void PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); };
        
        virtual void SetWindowProps(void) const {}
        virtual void SetLoggerProps(void) const {}
        
        static inline void EndApplication(void) { m_IsRunning = false; }
        
        inline Window* GetWindow(void) { return m_Window.get(); }
        inline ImGuiLayer* GetImGuiLayer(void) { return m_ImGuiLayer; }
        static inline Application* GetApplication(void) { return s_Instance; }
        
    private:
        bool OnWindowCloseEvent(WindowCloseEvent& event);
        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnWindowResizeEvent(WindowResizeEvent& event);
    private:
        Ref<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        
        LayerStack m_LayerStack;
        
        Object::Timer m_Timer;
        
        bool m_IsMinimized = false;
        
        static bool m_IsRunning;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication(void);

}
