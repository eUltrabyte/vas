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
        virtual ~Device();

        virtual uint32_t& GetQueueFamilyIndex();
        virtual uint32_t& GetQueueCount();
        virtual VkDevice GetDevice();

    private:
        uint32_t m_queueFamilyIndex;
        uint32_t m_queueCount;
        VkDevice m_device;

    };
};

#endif