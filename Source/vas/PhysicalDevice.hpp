#pragma once
#ifndef VAS_PHYSICAL_DEVICE_HEADER
#define VAS_PHYSICAL_DEVICE_HEADER

#include "vas.hpp"

namespace vas {
    struct VAS_API PhysicalDeviceCriteria {
        PhysicalDeviceCriteria() = default;
        PhysicalDeviceCriteria(const VkPhysicalDeviceProperties& physicalDeviceProperties, const VkPhysicalDeviceFeatures& physicalDeviceFeatures) 
        : physicalDeviceProperties(physicalDeviceProperties), physicalDeviceFeatures(physicalDeviceFeatures), check(true) { }
        ~PhysicalDeviceCriteria() = default;

        VkPhysicalDeviceProperties physicalDeviceProperties;
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        bool check = false;
    };

    class VAS_API PhysicalDevice {
    public:
        PhysicalDevice();
        PhysicalDevice(VkInstance instance, const PhysicalDeviceCriteria& physicalDeviceCriteria = PhysicalDeviceCriteria());
        virtual ~PhysicalDevice() = default;

        virtual VkPhysicalDeviceProperties& GetPhysicalDeviceProperties();
        virtual VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures();
        virtual VkPhysicalDevice GetPhysicalDevice();

    private:
        VkPhysicalDeviceProperties m_physicalDeviceProperties;
        VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
        VkPhysicalDevice m_physicalDevice;

    };
};

#endif