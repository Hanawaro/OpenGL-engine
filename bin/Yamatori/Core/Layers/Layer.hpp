#pragma once

#include <Yamatori/Logger/Logger.hpp>
#include <Yamatori/Core/Event/Input/Input.hpp>

namespace System {

    class Layer {
    public:
        Layer(const std::string& name = "") : m_DebugName(name) {}
        virtual ~Layer(void) = default;
        
        virtual void Attach(void) {}
        virtual void Detach(void) {}
        virtual void Update(float delta = 1.0f) {}
        virtual void Render(void) {}
        virtual void ImGuiRender(void) {}
        virtual void HandleEvent(Event& event) {}
        
        inline const std::string& GetName(void) const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };

}
