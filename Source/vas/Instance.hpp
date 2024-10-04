#pragma once
#ifndef VAS_INSTANCE_HEADER
#define VAS_INSTANCE_HEADER

#include "vas.hpp"

namespace vas {
    extern uint32_t vkGetAvailableVulkan();
    extern VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    extern void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    enum VAS_API InstanceVersion {
        Vulkan1_0,
        Vulkan1_1,
        Vulkan1_2,
        Vulkan1_3,
        VulkanAvailable
    };

    class VAS_API Instance {
    public:
        Instance(std::string_view title = "vas", std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>(), const InstanceVersion& instanceVersion = InstanceVersion::VulkanAvailable, bool validationLayers = false, bool debugMessenger = false);
        ~Instance();

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
            if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                VAS_LOG(pCallbackData->pMessage);
            }

            return VK_FALSE;
        }

        VkInstance GetInstance();
        VkDebugUtilsMessengerEXT GetDebugUtilsMessenger();

    private:
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugUtilsMessenger;
    
    };
};

#endif