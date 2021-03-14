#pragma once

#include <Yamatori/Core/Layers/Layer.hpp>

namespace System { namespace Interface {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(const std::string& debugName) : Layer(debugName) {}
        virtual ~ImGuiLayer(void) = default;
        
        virtual void AttachImpl(void) = 0;
        virtual void DetachImpl(void) = 0;
        
        virtual void BeginImpl(void) const = 0;
        virtual void EndImpl(void) const = 0;
        virtual void HandleEventImpl(Event& event) = 0;
        
        virtual void BlockEvents(bool block) = 0;
    };

} }
