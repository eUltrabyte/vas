#include "Instance.hpp"

namespace vas {
    Instance::Instance(std::string_view title, std::span<const char*> extensions, std::span<const char*> layers, const InstanceVersion& instanceVersion) {
        VkApplicationInfo applicationInfo { };
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pNext = nullptr;

        switch(instanceVersion) {
            case InstanceVersion::Vulkan1_0: applicationInfo.apiVersion = VK_API_VERSION_1_0; break;
            case InstanceVersion::Vulkan1_1: applicationInfo.apiVersion = VK_API_VERSION_1_1; break;
            case InstanceVersion::Vulkan1_2: applicationInfo.apiVersion = VK_API_VERSION_1_2; break;
            case InstanceVersion::Vulkan1_3: applicationInfo.apiVersion = VK_API_VERSION_1_3; break;
            case InstanceVersion::VulkanAvailable: applicationInfo.apiVersion = GetAvailableVulkan(); break;
        }

        VAS_LOG("api version - " + std::to_string(instanceVersion));

        applicationInfo.engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);
        applicationInfo.pEngineName = "vas";
        applicationInfo.applicationVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);
        applicationInfo.pApplicationName = title.data();

        VAS_LOG("app title - " + std::string(applicationInfo.pApplicationName));

        VkInstanceCreateInfo instanceCreateInfo { };
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount = extensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
        instanceCreateInfo.enabledLayerCount = layers.size();
        instanceCreateInfo.ppEnabledLayerNames = layers.data();

        VAS_LOG("extension count - " + std::to_string(instanceCreateInfo.enabledExtensionCount));
        VAS_LOG("layer count - " + std::to_string(instanceCreateInfo.enabledLayerCount));

        VAS_ASSERT(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));
        VAS_LOG("instance created");
    }

    Instance::~Instance() {
        vkDestroyInstance(GetInstance(), nullptr);
        VAS_LOG("instance destroyed");
    }

    uint32_t Instance::GetAvailableVulkan() {
        uint32_t version = VK_API_VERSION_1_0;
        auto EnumerateInstanceVersion = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
        if(EnumerateInstanceVersion != nullptr) {
            EnumerateInstanceVersion(&version);
        } else {
            return 0;
        }

        return version;
    }

    VkInstance Instance::GetInstance() {
        if(m_instance != VK_NULL_HANDLE) {
            return m_instance;
        } else {
            return nullptr;
        }
    }
};