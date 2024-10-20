#pragma once
#ifndef VAS_DEVICE_HEADER
#define VAS_DEVICE_HEADER

#include "vas.hpp"

namespace vas {
    struct VAS_API DeviceProps {
        DeviceProps(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits = VK_QUEUE_GRAPHICS_BIT) 
        : physicalDevice(physicalDevice), physicalDeviceFeatures(physicalDeviceFeatures), queueFlagBits(queueFlagBits) { }
        ~DeviceProps() = default;

        VkPhysicalDevice physicalDevice;
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        VkQueueFlagBits queueFlagBits;
    };

    class VAS_API Device {
    public:
        Device();
        Device(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits = VK_QUEUE_GRAPHICS_BIT);
        Device(const DeviceProps& deviceProps);
        ~Device();

        VkDevice GetDevice();

    private:
        VkDevice m_device;

    };
};

#endif