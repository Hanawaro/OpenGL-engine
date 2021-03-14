#include <ymtpch.hpp>
#include "vkWindowImpl.hpp"

#include <Yamatori/Core/Core.hpp>

#define YAMATORI_GLFW_BOOL(condition) condition ? GLFW_TRUE : GLFW_FALSE

namespace System { namespace VK { namespace Impl {

    Window::Window(void) : m_Window(nullptr) {
        
        GLFW::Init();
        GLFW::Hint(GLFW_CLIENT_API, GLFW_NO_API);
        
        ReCreate();
        GLFW::SetCallbacks(m_Window);
        
        uint32_t extensionCount = 0;
        const char** extensionNames = glfwGetRequiredInstanceExtensions(&extensionCount);
        
        Vulkan::Init(extensionCount, extensionNames);
    }

    Window::~Window(void) {
        GLFW::DestroyWindow(m_Window);
        GLFW::Terminate();
    }

    void Window::ReCreate(void) {
        if (m_IsWindowCreated)
            GLFW::DestroyWindow(m_Window);
        m_Window = GLFW::CreateWindow();
        
        GLFW::SetWindowSizeLimits(m_Window, m_MinimalWidth / s_Scale, m_MinimalHeight / s_Scale, GLFW_DONT_CARE, GLFW_DONT_CARE);
        GLFW::SetWindowUserPointer(m_Window, this);
    }

    void Window::Update(void) {
        GLFW::PollEvents();
        GLFW::SwapBuffers(m_Window);
    }

    void Window::SetVSync(bool enabled) {
        if ((WindowProps::vSyncEnable = enabled)) {
            
        } else {
            
        }
    }
    
} } }
