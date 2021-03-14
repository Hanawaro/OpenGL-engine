#include <ymtpch.hpp>
#include "LayerStack.hpp"

namespace System {

    LayerStack::LayerStack(void) : m_CurrentStackTop(0) {}

    LayerStack::~LayerStack(void) {
        for (auto& layer : m_Layers) {
            layer->Detach();
            delete layer;
        }
    }
    
    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_CurrentStackTop, layer);
        m_CurrentStackTop++;
        layer->Attach();
    }

    void LayerStack::PushOverlay(Layer* layer) {
        m_Layers.emplace_back(layer);
        layer->Attach();
    }
    
    void LayerStack::PopLayer(Layer* layer) {
        auto find = std::find(m_Layers.begin(), m_Layers.end() + m_CurrentStackTop, layer);
        if (find != m_Layers.begin() + m_CurrentStackTop) {
            m_Layers.erase(find);
            m_CurrentStackTop--;
            layer->Detach();
        }
    }

    void LayerStack::PopOverlay(Layer* layer) {
        auto find = std::find(m_Layers.begin() + m_CurrentStackTop, m_Layers.end(), layer);
        if (find != m_Layers.end()) {
            m_Layers.erase(find);
            layer->Detach();
        }
    }

}
