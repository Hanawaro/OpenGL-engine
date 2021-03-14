#pragma once

#include <Yamatori/Core/Window/WindowInterface.hpp>
#include "Vulkan/Vulkan.hpp"
#include <GraphicsAPI/WindowCreater/GLFW/GLFW.hpp>

namespace System { namespace VK { namespace Impl {

    class Window final : public Interface::Window {
    public:
        Window(void);
        virtual ~Window(void);
        
        virtual void Update(void) override;
        virtual void SetCallBackEvent(std::function<void(Event&)> callback) override { m_Callback = callback; };
        
        virtual inline std::pair<uint32_t, uint32_t> GetSize(void) const override {
            return std::make_pair(WindowProps::width, WindowProps::height);
        }
        
        virtual void ReCreate(void) override;
        virtual void Callback(Event& event) const override { m_Callback(event); };
        
        virtual inline uint32_t GetWidth(void) const override { return WindowProps::width; };
        virtual inline uint32_t GetHeight(void) const override { return WindowProps::height; };
        
        virtual inline bool GetVSync(void) const override { return WindowProps::vSyncEnable; };
        virtual void SetVSync(bool enabled) override;
        
        virtual inline void* GetNativeWindow(void) const override { return static_cast<void*>(m_Window); };
    private:
        GLFWwindow* m_Window;
        std::function<void(Event&)> m_Callback;
        
        bool m_IsWindowCreated = false;
        
        const uint32_t m_MinimalWidth = 800;
        const uint32_t m_MinimalHeight = 600;
    };

} } }
