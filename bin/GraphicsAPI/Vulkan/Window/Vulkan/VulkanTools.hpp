#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace System { namespace VulkanTools {
    
    bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers);
    bool CheckExtensionsSupport(const std::vector<const char*>& extension);
    
    VkDebugUtilsMessengerCreateInfoEXT CreaetDebugUnil(void);
    
} }
