#include "Instance.hpp"

namespace vas {
    uint32_t vkGetAvailableVulkan() {
        uint32_t version = VK_API_VERSION_1_0;
        auto pfnEnumerateInstanceVersion = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
        if(pfnEnumerateInstanceVersion != nullptr) {
            pfnEnumerateInstanceVersion(&version);
        } else {
            return 0;
        }

        return version;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto pfnCreateDebugUtilsMessengerEXT = PFN_vkCreateDebugUtilsMessengerEXT(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if(pfnCreateDebugUtilsMessengerEXT != nullptr) {
            return pfnCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto pfnDestroyDebugUtilsMessengerEXT = PFN_vkDestroyDebugUtilsMessengerEXT(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if(pfnDestroyDebugUtilsMessengerEXT != nullptr) {
            pfnDestroyDebugUtilsMessengerEXT(instance, debugMessenger, pAllocator);
        }
    }

    Instance::Instance(std::string_view title, std::span<const char*> extensions, std::span<const char*> layers, const InstanceVersion& instanceVersion, bool validationLayers, bool debugMessenger, PFN_vkDebugUtilsMessengerCallbackEXT debugMessengerCallback) {
        VkApplicationInfo applicationInfo { };
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pNext = nullptr;

        switch(instanceVersion) {
            case InstanceVersion::Vulkan1_0: applicationInfo.apiVersion = VK_API_VERSION_1_0; break;
            case InstanceVersion::Vulkan1_1: applicationInfo.apiVersion = VK_API_VERSION_1_1; break;
            case InstanceVersion::Vulkan1_2: applicationInfo.apiVersion = VK_API_VERSION_1_2; break;
            case InstanceVersion::Vulkan1_3: applicationInfo.apiVersion = VK_API_VERSION_1_3; break;
            case InstanceVersion::VulkanAvailable: applicationInfo.apiVersion = vkGetAvailableVulkan(); break;
        }

        VAS_LOG("api version - " + std::to_string(instanceVersion));

        applicationInfo.engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);
        applicationInfo.pEngineName = "vas";
        applicationInfo.applicationVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);
        applicationInfo.pApplicationName = title.data();

        VAS_LOG("app title - " + std::string(applicationInfo.pApplicationName));

        std::vector<const char*> modifiedExtensions;
        modifiedExtensions.assign(extensions.begin(), extensions.end());
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo { };
        if(debugMessenger) {
            modifiedExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugUtilsMessengerCreateInfo.pNext = nullptr;
            debugUtilsMessengerCreateInfo.flags = 0;
            debugUtilsMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugUtilsMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            
            if(debugMessengerCallback) {
                debugUtilsMessengerCreateInfo.pfnUserCallback = debugMessengerCallback;
            } else {
                debugUtilsMessengerCreateInfo.pfnUserCallback = DebugUtilsMessengerCallback;
            }

            debugUtilsMessengerCreateInfo.pUserData = nullptr;
        }

        std::vector<const char*> modifiedLayers;
        modifiedLayers.assign(layers.begin(), layers.end());
        if(validationLayers) {
            modifiedLayers.emplace_back("VK_LAYER_KHRONOS_validation");
        }

        VkInstanceCreateInfo instanceCreateInfo { };
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = debugMessenger ? &debugUtilsMessengerCreateInfo : nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount = modifiedExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = modifiedExtensions.data();
        instanceCreateInfo.enabledLayerCount = modifiedLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = modifiedLayers.data();

        VAS_LOG("extension count - " + std::to_string(instanceCreateInfo.enabledExtensionCount));
        VAS_LOG("layer count - " + std::to_string(instanceCreateInfo.enabledLayerCount));

        VAS_ASSERT(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));

        if(debugMessenger) {
            VAS_ASSERT(CreateDebugUtilsMessengerEXT(m_instance, &debugUtilsMessengerCreateInfo, nullptr, &m_debugUtilsMessenger));
        }

        VAS_LOG("instance created");
    }

    Instance::Instance(const InstanceProps& instanceProps)
    : Instance(instanceProps.title, instanceProps.extensions, instanceProps.layers, instanceProps.instanceVersion, instanceProps.validationLayers, instanceProps.debugMessenger, instanceProps.debugMessengerCallback) { }

    Instance::~Instance() {
        if(m_debugUtilsMessenger != VK_NULL_HANDLE) {
            DestroyDebugUtilsMessengerEXT(GetInstance(), GetDebugUtilsMessenger(), nullptr);
        }

        vkDestroyInstance(GetInstance(), nullptr);
        VAS_LOG("instance destroyed");
    }

    VkInstance Instance::GetInstance() {
        if(m_instance != VK_NULL_HANDLE) {
            return m_instance;
        } else {
            VAS_LOG("accessing instance while being undefined");
            return nullptr;
        }
    }

    VkDebugUtilsMessengerEXT Instance::GetDebugUtilsMessenger() {
        if(m_debugUtilsMessenger != VK_NULL_HANDLE) {
            return m_debugUtilsMessenger;
        } else {
            VAS_LOG("accessing debug utils messenger while being undefined");
            return nullptr;
        }
    }
};