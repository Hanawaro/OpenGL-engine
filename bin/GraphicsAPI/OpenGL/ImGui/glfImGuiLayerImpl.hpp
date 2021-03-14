#pragma once

#include <Yamatori/ImGui/ImGuiLayerInterface.hpp>

namespace System { namespace GL { namespace Impl {

    class ImGuiLayer final : public Interface::ImGuiLayer {
    public:
        ImGuiLayer(const std::string& debugName = "") : Interface::ImGuiLayer(debugName) {}
        virtual ~ImGuiLayer(void) = default;
        
        virtual void AttachImpl(void) override;
        virtual void DetachImpl(void) override;
        
        virtual void BeginImpl(void) const override;
        virtual void EndImpl(void) const override;
        
        virtual void HandleEventImpl(Event& event) override;
        
        virtual void BlockEvents(bool block) override { m_IsBlock = block; }
    private:
        bool m_IsBlock = false;
        float m_Time = 0.0f;
    };

} } }
