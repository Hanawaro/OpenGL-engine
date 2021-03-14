#include <ymtpch.hpp>
#include "GLFW.hpp"

#include <Yamatori/Core/Window/WindowInterface.hpp>

#define YAMATORI_GLFW_BOOL(condition) condition ? GLFW_TRUE : GLFW_FALSE

namespace System {
    
    bool GLFW::s_Initialize = false;
    
    static void glfwErrorCallback(int error, const char* description) {
        _err << "GLFW Error " << error << ": " << description << end;
    }
    
    void GLFW::Init(void) {
        if (s_Initialize) return;
        
        if (!glfwInit()) {
            _err << "GLFW could not initialize" << end;
            s_Initialize = false;
            return;
        }
        
        glfwSetErrorCallback(glfwErrorCallback);
        s_Initialize = true;
    }
    
    void GLFW::Terminate(void) {
        if (!s_Initialize) return;
        glfwTerminate();
    }
    
    void GLFW::Hint(int hint, int value) {
        if (!s_Initialize) return;
        glfwWindowHint(hint, value);
    }
    
    GLFWwindow* GLFW::CreateWindow(void) {
        if (!s_Initialize) return nullptr;
        
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(monitor);
        
        uint32_t width  = WindowProps::width;
        uint32_t height = WindowProps::height;
        
        switch (WindowProps::mode) {
            case WindowProps::Mode::Window:
                glfwWindowHint(GLFW_RESIZABLE, YAMATORI_GLFW_BOOL(WindowProps::resizeEnable));
                glfwWindowHint(GLFW_DECORATED, YAMATORI_GLFW_BOOL(WindowProps::borderEnable));
                monitor = nullptr;
                break;
            case WindowProps::Mode::FullscreenWindow:
                glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
                
                width = mode->width * s_Scale;
                height = mode->height * s_Scale;
                
                monitor = nullptr;
                break;
            case WindowProps::Mode::Fullscreen:
                if (!(width = WindowProps::fullscreenWidth))
                    width = mode->width * s_Scale;
                if (!(height = WindowProps::fullscreenHeight))
                    height = mode->height * s_Scale;
                break;
            case WindowProps::Mode::MaximizedWindow:
                glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
                glfwWindowHint(GLFW_RESIZABLE, YAMATORI_GLFW_BOOL(WindowProps::resizeEnable));
                glfwWindowHint(GLFW_DECORATED, YAMATORI_GLFW_BOOL(WindowProps::borderEnable));
                
                monitor = nullptr;
                break;
        }
        
        GLFWwindow* window = glfwCreateWindow(width / s_Scale, height / s_Scale, WindowProps::title.c_str(), monitor, nullptr);
        glfwGetFramebufferSize(window, (int*)&WindowProps::width, (int*)&WindowProps::height);
        
        if (!window) {
            _err << "GLFW window could not create" << end;
            return nullptr;
        }
        
        return window;
    }
    
    void GLFW::DestroyWindow(GLFWwindow* window) {
        if (!s_Initialize) return;
        glfwDestroyWindow(window);
    }
    
    void GLFW::PollEvents(void) {
        if (!s_Initialize) return;
        glfwPollEvents();
    }
    
    void GLFW::SwapBuffers(GLFWwindow* window) {
        if (!s_Initialize) return;
        glfwSwapBuffers(window);
    }
    
    void GLFW::SwapInterval(int interval) {
        if (!s_Initialize) return;
        glfwSwapInterval(interval);
    }
    
    void GLFW::MakeContextCurrent(GLFWwindow* window) {
        if (!s_Initialize) return;
        glfwMakeContextCurrent(window);
    }
    
    void GLFW::SetWindowSizeLimits(GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight) {
        if (!s_Initialize) return;
        glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
    }
    
    void GLFW::SetWindowUserPointer(GLFWwindow* window, void* pointer) {
        if (!s_Initialize) return;
        glfwSetWindowUserPointer(window, pointer);
    }
    
    
    void GLFW::SetCallbacks(GLFWwindow* window) {
        if (!s_Initialize) return;
        
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            WindowProps::width = width;
            WindowProps::height = height;

            WindowResizeEvent event(WindowProps::width, WindowProps::height);
            data->Callback(event);
        });
        
        glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            
            if (iconified) {
                WindowResizeEvent event(0, 0);
                data->Callback(event);
            } else {
                WindowResizeEvent event(WindowProps::width, WindowProps::height);
                data->Callback(event);
            }
            
        });
        
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data->Callback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data->Callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data->Callback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data->Callback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data->Callback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data->Callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data->Callback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data->Callback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            auto data = (Interface::Window*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data->Callback(event);
        });
    }
    
};
