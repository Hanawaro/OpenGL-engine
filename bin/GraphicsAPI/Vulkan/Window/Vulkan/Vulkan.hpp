#pragma once

#include "VulkanTools.hpp"

namespace System {
    
    class Vulkan {
    public:
        Vulkan(void) = delete;
        Vulkan(const Vulkan&) = delete;
        Vulkan& operator=(const Vulkan&) = delete;
        
        static void Init(uint32_t extensionCount, const char** extensionNames);
        static void ShutDown(void);
    private:
        static bool CreateInstance(const std::vector<const char*>& extensions, const std::vector<const char*>& validationLayers);
    private:
        static VkInstance s_Instance;
        
        static const bool s_ValidationLayers = true;
        
        static bool s_IsInit;
    };
    
}
