#pragma once

#include "ImGuiLayerInterface.hpp"

namespace System {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(const std::string& debugName = "");
        virtual ~ImGuiLayer(void);
        
        virtual void Attach(void) override { m_Instance->AttachImpl(); }
        virtual void Detach(void) override { m_Instance->DetachImpl(); }
        
        void Begin(void) const { m_Instance->BeginImpl(); }
        void End(void) const { m_Instance->EndImpl(); }
        
        inline void HandleEvent(Event& event) override { m_Instance->HandleEventImpl(event); }
        
        inline void BlockEvents(bool block) { m_Instance->BlockEvents(block); }
    private:
        Interface::ImGuiLayer* m_Instance;
    };
}
