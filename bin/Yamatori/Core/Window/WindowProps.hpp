#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System {

    struct WindowProps {
    public:
        enum class Mode {
            Window,
            MaximizedWindow,
            FullscreenWindow,
            Fullscreen
        };
        enum class GraphicAPI {
            OpenGL,
            DirectX,
            Vulkan,
            Metal
        };
    public:
        WindowProps(void) = delete;
        WindowProps(const WindowProps&) = delete;
        WindowProps& operator=(const WindowProps&) = delete;
        
        static std::string title;
        static Mode mode;
        static GraphicAPI graphicAPI;
        static uint32_t width;
        static uint32_t height;
        static uint32_t fullscreenWidth;
        static uint32_t fullscreenHeight;
        static uint16_t frameRate;
        static bool vSyncEnable;
        static bool resizeEnable;
        static bool borderEnable;
        
        static std::string configPath;
        static bool configEnable;
    };

}
