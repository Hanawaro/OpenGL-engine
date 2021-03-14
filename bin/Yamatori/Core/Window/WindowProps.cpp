#include <ymtpch.hpp>
#include "WindowProps.hpp"

namespace System {
    
    WindowProps::Mode WindowProps::mode             = WindowProps::Mode::Window;
    WindowProps::GraphicAPI WindowProps::graphicAPI = WindowProps::GraphicAPI::OpenGL;
    
    std::string WindowProps::title         = "Yamatori application";
    uint32_t WindowProps::width            = 800;
    uint32_t WindowProps::height           = 600;
    uint32_t WindowProps::fullscreenWidth  = NULL;
    uint32_t WindowProps::fullscreenHeight = NULL;
    uint16_t WindowProps::frameRate        = 144;
    bool WindowProps::vSyncEnable          = true;
    bool WindowProps::resizeEnable         = true;
    bool WindowProps::borderEnable         = true;
    
    std::string WindowProps::configPath = "cfg/WindowProps.cfg";
    bool WindowProps::configEnable      = false;

}
