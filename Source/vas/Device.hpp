#pragma once
#ifndef VAS_DEVICE_HEADER
#define VAS_DEVICE_HEADER

#include "vas.hpp"

namespace vas {
    struct VAS_API DeviceProps {
        DeviceProps(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits = VK_QUEUE_GRAPHICS_BIT, std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>()) 
        : physicalDevice(physicalDevice), physicalDeviceFeatures(physicalDeviceFeatures), queueFlagBits(queueFlagBits), extensions(extensions), layers(layers) { }
        ~DeviceProps() = default;

        VkPhysicalDevice physicalDevice;
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        VkQueueFlagBits queueFlagBits;
        std::span<const char*> extensions;
        std::span<const char*> layers;
    };

    class VAS_API Device {
    public:
        Device();
        Device(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits = VK_QUEUE_GRAPHICS_BIT, std::span<const char*> extensions = std::span<const char*>(), std::span<const char*> layers = std::span<const char*>());
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