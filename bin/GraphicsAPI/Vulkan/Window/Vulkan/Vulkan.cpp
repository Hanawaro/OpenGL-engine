#include <ymtpch.hpp>
#include "Vulkan.hpp"

#include <Yamatori/Core/Window/WindowProps.hpp>

namespace System {
    
    VkInstance Vulkan::s_Instance;
    bool Vulkan::s_IsInit = false;
    
    
    
    void Vulkan::Init(uint32_t extensionCount, const char** extensionNames) {
        
        std::vector<const char*> validationLayers;
        std::vector<const char*> extensions(extensionNames, extensionNames + extensionCount);
        
        if (s_ValidationLayers) {
            validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        
        
        if (!CreateInstance(extensions, validationLayers)) return;
        
        _scs << "vulkan is working" << end;
    }
    
    bool Vulkan::CreateInstance(const std::vector<const char*>& extensions, const std::vector<const char*>& validationLayers) {
        VkApplicationInfo appInfo;
        memset(&appInfo, 0, sizeof(appInfo));
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = WindowProps::title.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Yamatori";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        
        VkInstanceCreateInfo createInfo;
        memset(&createInfo, 0, sizeof(createInfo));
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        if (VulkanTools::CheckExtensionsSupport(extensions)) {
            createInfo.enabledExtensionCount = (uint32_t) extensions.size();
            createInfo.ppEnabledExtensionNames = extensions.data();
        }
    
        if (VulkanTools::checkValidationLayerSupport(validationLayers) && s_ValidationLayers) {
            createInfo.enabledLayerCount = (uint32_t) validationLayers.size();
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
    
        if (vkCreateInstance(&createInfo, nullptr, &s_Instance) != VK_SUCCESS) {
            _err << "Failed to create instance" << end;
            return false;
        }
        return true;
    }
    
    void Vulkan::ShutDown(void) {
        vkDestroyInstance(s_Instance, nullptr);
    }
    
}
