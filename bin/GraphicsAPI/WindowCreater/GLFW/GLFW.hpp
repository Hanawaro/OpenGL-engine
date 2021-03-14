#pragma once

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <Yamatori/Core/Core.hpp>
#include <GLFW/glfw3.h>

namespace System {
    
    class GLFW {
    public:
        GLFW(void) = delete;
        GLFW(const GLFW&) = delete;
        GLFW& operator=(const GLFW&) = delete;
        
        static void Init(void);
        static void Terminate(void);
        
        static void Hint(int hint, int value);
        
        static GLFWwindow* CreateWindow(void);
        static void DestroyWindow(GLFWwindow* window);
        
        static void PollEvents(void);
        static void SwapBuffers(GLFWwindow* window);
        
        static void SwapInterval(int interval);
        static void SetCallbacks(GLFWwindow* window);
        
        static void MakeContextCurrent(GLFWwindow* window);
        static void SetWindowSizeLimits(GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight);
        static void SetWindowUserPointer(GLFWwindow* window, void* pointer);
        
        static inline bool IsInit(void) { return s_Initialize; }
    private:
        static bool s_Initialize;
    };
    
}
