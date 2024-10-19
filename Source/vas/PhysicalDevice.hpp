#pragma once
#ifndef VAS_PHYSICAL_DEVICE_HEADER
#define VAS_PHYSICAL_DEVICE_HEADER

#include "vas.hpp"

namespace vas {
    class VAS_API PhysicalDevice {
    public:
        PhysicalDevice();
        PhysicalDevice(VkInstance instance);
        ~PhysicalDevice() = default;

        VkPhysicalDeviceProperties GetPhysicalDeviceProperties();
        VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures();
        VkPhysicalDevice GetPhysicalDevice();

    private:
        VkPhysicalDeviceProperties m_physicalDeviceProperties;
        VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
        VkPhysicalDevice m_physicalDevice;

    };
};

#endif