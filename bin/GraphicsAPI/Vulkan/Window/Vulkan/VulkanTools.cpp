#include "VulkanTools.hpp"

namespace System { namespace VulkanTools {
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        _err << "validation layer: " << pCallbackData->pMessage << end;
        return VK_FALSE;
    }
    
    bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers) {
        uint32_t availableLayerCount = 0;
        vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(availableLayerCount);
        vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data());
        
        for (auto& layerName : validationLayers) {
            bool layerFound = false;
            for (auto& layerProperties : availableLayers) {
                if (!strcmp(layerName, layerProperties.layerName)) {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound)
                return false;
        }
        
        return true;
    }
    
    bool CheckExtensionsSupport(const std::vector<const char*>& extensions) {
        uint32_t availableExtensionsCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
        std::vector<VkLayerProperties> availableExtensions(availableExtensionsCount);
        vkEnumerateInstanceLayerProperties(&availableExtensionsCount, availableExtensions.data());

        for (auto& extension : extensions) {
            bool layerFound = false;
            for (auto& availableExtension : availableExtensions) {
                if (!strcmp(extension, availableExtension.layerName)) {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound)
                return false;
        }

        return true;
    }
    
    VkDebugUtilsMessengerCreateInfoEXT CreaetDebugUnil(void) {
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        memset(&createInfo, 0, sizeof(createInfo));
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
        
        return createInfo;
    }
    
} }
