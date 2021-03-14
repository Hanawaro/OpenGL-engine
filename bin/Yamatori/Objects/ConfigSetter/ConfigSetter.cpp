#include <ymtpch.hpp>
#include "ConfigSetter.hpp"

#include "WindowPropsConfig"

namespace System { namespace Object {

    static const std::string defaultTitle         = "Yamatori application";
    static const uint32_t defaultWidth            = 800;
    static const uint32_t defaultHeight           = 600;
    static const uint32_t defaultFullscreenWidth  = NULL;
    static const uint32_t defaultFullscreenHeight = NULL;
    static const uint16_t defaultFrameRate        = 144;
    static const bool defaultVSyncEnable          = true;
    static const bool defaultResizeEnable         = true;
    static const bool defaultBorderEnable         = true;

    static const WindowProps::Mode defaultMode = WindowProps::Mode::Window;
    static const WindowProps::GraphicAPI defaultGraphicAPI = WindowProps::GraphicAPI::OpenGL;

    void ConfigSetter::SetProperties(void) {
        if (!Object::ConfigReader::Read(WindowProps::configPath, 11, 1)) {
            std::ofstream newCfg(WindowProps::configPath);
            newCfg << cfdData;
            newCfg.close();
            if (!Object::ConfigReader::Read(WindowProps::configPath, 11, 1))
                return;
        }
        
        SetWindowProp("Title", [](const std::string& data, bool status) {
            WindowProps::title = status ? data : defaultTitle;
            return false;
        });
        
        SetWindowProp("Width", [](const std::string& data, bool status) {
            WindowProps::width = status ? (uint32_t) strtoul(data.c_str(), nullptr, 0) : defaultWidth;
            return false;
        });
        
        SetWindowProp("Height", [](const std::string& data, bool status) {
            WindowProps::height = status ? (uint32_t) strtoul(data.c_str(), nullptr, 0) : defaultHeight;
            return false;
        });
        
        SetWindowProp("FullscreenWidth", [](const std::string& data, bool status) {
            WindowProps::fullscreenWidth = status ? (uint32_t) strtoul(data.c_str(), nullptr, 0) : defaultFullscreenWidth;
            return false;
        });
        
        SetWindowProp("FullscreenHeight", [](const std::string& data, bool status) {
            WindowProps::fullscreenHeight = status ? (uint32_t) strtoul(data.c_str(), nullptr, 0) : defaultFullscreenHeight;
            return false;
        });
        
        SetWindowProp("FrameRate", [](const std::string& data, bool status) {
            WindowProps::frameRate = status ? (uint32_t) strtoul(data.c_str(), nullptr, 0) : defaultFrameRate;
            return false;
        });
        
        SetWindowProp("VSyncEnable", [](const std::string& data, bool status) {
            if (!status) {
                WindowProps::vSyncEnable = defaultVSyncEnable;
                return false;
            }
            std::string tmpData = data;
            std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
            if (tmpData == "true") {
                WindowProps::vSyncEnable = true;
                return false;
            } else if (tmpData == "false") {
                WindowProps::vSyncEnable = false;
                return false;
            }
            WindowProps::vSyncEnable = defaultVSyncEnable;
            return true;
        });

        SetWindowProp("ResizeEnable", [](const std::string& data, bool status) {
            if (!status) {
                WindowProps::resizeEnable = defaultResizeEnable;
                return false;
            }
            std::string tmpData = data;
            std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
            if (tmpData == "true") {
                WindowProps::resizeEnable = true;
                return false;
            } else if (tmpData == "false") {
                WindowProps::resizeEnable = false;
                return false;
            }
            WindowProps::resizeEnable = defaultResizeEnable;
            return true;
        });
        
        SetWindowProp("BorderEnable", [](const std::string& data, bool status) {
            if (!status) {
                WindowProps::borderEnable = defaultBorderEnable;
                return false;
            }
            std::string tmpData = data;
            std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
            if (tmpData == "true") {
                WindowProps::borderEnable = true;
                return false;
            } else if (tmpData == "false") {
                WindowProps::borderEnable = false;
                return false;
            }
            WindowProps::borderEnable = defaultBorderEnable;
            return true;
        });
        
        SetWindowProp("Mode", [](const std::string& data, bool status) {
            if (!status) {
                WindowProps::mode = defaultMode;
                return false;
            }
            std::string tmpData = data;
            std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
            if (tmpData == "window") {
                WindowProps::mode = WindowProps::Mode::Window;
                return false;
            } else if (tmpData == "fullscreen") {
                WindowProps::mode = WindowProps::Mode::Fullscreen;
                return false;
            } else if (tmpData == "fullscreenwindow") {
                WindowProps::mode = WindowProps::Mode::FullscreenWindow;
                return false;
            } else if (tmpData == "maximizedwindow") {
                WindowProps::mode = WindowProps::Mode::MaximizedWindow;
                return false;
            }
            WindowProps::mode = defaultMode;
            return true;
        });
        
        SetWindowProp("GraphicAPI", [](const std::string& data, bool status) {
            if (!status) {
                WindowProps::graphicAPI = defaultGraphicAPI;
                return false;
            }
            std::string tmpData = data;
            std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
            if (tmpData == "opengl") {
                WindowProps::graphicAPI = WindowProps::GraphicAPI::OpenGL;
                return false;
            } else if (tmpData == "directx") {
                WindowProps::graphicAPI = WindowProps::GraphicAPI::DirectX;
                return false;
            } else if (tmpData == "Vulkan") {
                WindowProps::graphicAPI = WindowProps::GraphicAPI::Vulkan;
                return false;
            } else if (tmpData == "metal") {
                WindowProps::graphicAPI = WindowProps::GraphicAPI::Metal;
                return false;
            }
            WindowProps::graphicAPI = defaultGraphicAPI;
            return true;
        });

    }

} }
