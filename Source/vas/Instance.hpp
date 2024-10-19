#pragma once
#ifndef VAS_INSTANCE_HEADER
#define VAS_INSTANCE_HEADER

#include "vas.hpp"

namespace vas {
    extern uint32_t GetAvailableVulkan();
    extern VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    extern void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    enum VAS_API InstanceVersion {
        Vulkan1_0,
        Vulkan1_1,
        Vulkan1_2,
        Vulkan1_3,
        VulkanAvailable
    };

    struct VAS_API InstanceProps {
        InstanceProps(std::string_view title = "vas", std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>(), const InstanceVersion& instanceVersion = InstanceVersion::VulkanAvailable, bool validationLayers = false, bool debugMessenger = false, PFN_vkDebugUtilsMessengerCallbackEXT debugMessengerCallback = nullptr) 
        : title(title), extensions(extensions), layers(layers), instanceVersion(instanceVersion), validationLayers(validationLayers), debugMessenger(debugMessenger), debugMessengerCallback(debugMessengerCallback) { }
        ~InstanceProps() = default;

        std::string_view title;
        std::span<const char*> extensions;
        std::span<const char*> layers;
        InstanceVersion instanceVersion;
        bool validationLayers;
        bool debugMessenger;
        PFN_vkDebugUtilsMessengerCallbackEXT debugMessengerCallback;
    };

    class VAS_API Instance {
    public:
        Instance(std::string_view title = "vas", std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>(), const InstanceVersion& instanceVersion = InstanceVersion::VulkanAvailable, bool validationLayers = false, bool debugMessenger = false, PFN_vkDebugUtilsMessengerCallbackEXT debugMessengerCallback = nullptr);
        Instance(const InstanceProps& instanceProps);
        ~Instance();

        virtual bool IsExtensionAvailable(std::string_view extensionName);
        virtual bool IsLayerAvailable(std::string_view layerName);

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
            if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT && messageSeverity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                VAS_LOG(pCallbackData->pMessage);
            } else if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                VAS_ERROR(pCallbackData->pMessage);
            } else if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                VAS_FATAL(pCallbackData->pMessage);
            }

            return VK_FALSE;
        }

        VkInstance GetInstance();
        VkDebugUtilsMessengerEXT GetDebugUtilsMessenger();

    private:
        std::vector<VkExtensionProperties> m_extensionsProperties;
        std::vector<VkLayerProperties> m_layersProperties;
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugUtilsMessenger;
    
    };
};

#endif