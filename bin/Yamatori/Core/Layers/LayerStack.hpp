#pragma once

#include "Layer.hpp"

namespace System {

    class LayerStack {
    public:
        LayerStack(void);
        ~LayerStack(void);
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);
        
        std::vector<Layer*>::iterator begin(void) { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator begin(void) const { return m_Layers.begin(); }
        
        std::vector<Layer*>::iterator end(void) { return m_Layers.end(); }
        std::vector<Layer*>::const_iterator end(void) const { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_CurrentStackTop;
    };

}
