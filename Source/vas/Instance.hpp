#pragma once
#ifndef VAS_INSTANCE_HEADER
#define VAS_INSTANCE_HEADER

#include "vas.hpp"

namespace vas {
    enum VAS_API InstanceVersion {
        Vulkan1_0,
        Vulkan1_1,
        Vulkan1_2,
        Vulkan1_3,
        VulkanAvailable
    };

    class VAS_API Instance {
    public:
        Instance(std::string_view title = "vas", std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>(), const InstanceVersion& instanceVersion = InstanceVersion::VulkanAvailable);
        ~Instance();

        static uint32_t GetAvailableVulkan();

        VkInstance GetInstance();

    private:
        VkInstance m_instance;
    
    };
};

#endif