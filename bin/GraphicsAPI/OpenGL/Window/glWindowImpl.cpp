#include <ymtpch.hpp>
#include "glWindowImpl.hpp"

#include <Yamatori/Core/Core.hpp>

#define YAMATORI_GLFW_BOOL(condition) condition ? GLFW_TRUE : GLFW_FALSE

namespace System { namespace GL { namespace Impl {

    Window::Window(void) : m_Window(nullptr) {
        GLFW::Init();
        GLFW::Hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        GLFW::Hint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFW::Hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFW::Hint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        
        ReCreate();
        GLFW::SetCallbacks(m_Window);
        
        GLEW::Init();
    }

    Window::~Window(void) {
        GLFW::DestroyWindow(m_Window);
        GLFW::Terminate();
    }

    void Window::ReCreate(void) {
        if (m_IsWindowCreated)
            GLFW::DestroyWindow(m_Window);
        m_Window = GLFW::CreateWindow();
        
        GLFW::MakeContextCurrent(m_Window);
        GLFW::SetWindowSizeLimits(m_Window, m_MinimalWidth / s_Scale, m_MinimalHeight / s_Scale, GLFW_DONT_CARE, GLFW_DONT_CARE);
        GLFW::SetWindowUserPointer(m_Window, this);
        
        SetVSync(WindowProps::vSyncEnable);
        
        glViewport(0, 0, WindowProps::width, WindowProps::height);
        
        m_IsWindowCreated = true;
    }

    void Window::Update(void) {
        GLFW::PollEvents();
        GLFW::SwapBuffers(m_Window);
    }

    void Window::SetVSync(bool enabled) {
        if ((WindowProps::vSyncEnable = enabled)) {
            GLFW::SwapInterval(1);
        } else {
            GLFW::SwapInterval(0);
        }
    }
    
} } }
