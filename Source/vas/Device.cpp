#include "Device.hpp"

namespace vas {
    Device::Device() { }
    
    Device::Device(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        uint32_t queueFamilyIndex = -1;
        for(int i = 0; i < queueFamilies.size(); ++i) {
            if(queueFamilies[i].queueFlags & queueFlagBits) {
                VAS_LOG("queue family - " + std::to_string(i));
                queueFamilyIndex = i;
                break;
            }
        }

        if(queueFamilyIndex == -1) {
            VAS_LOG("none of queue families are suitable, using first available");
            queueFamilyIndex = 0;
        }

        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo deviceQueueCreateInfo { };
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pNext = nullptr;
        deviceQueueCreateInfo.flags = 0;
        deviceQueueCreateInfo.queueCount = 1;
        deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo deviceCreateInfo { };
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = nullptr;
        deviceCreateInfo.flags = 0;
        deviceCreateInfo.enabledExtensionCount = 0;
        deviceCreateInfo.ppEnabledExtensionNames = nullptr;
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.ppEnabledLayerNames = nullptr;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

        VAS_ASSERT(vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &m_device));

        VAS_LOG("device created");
    }

    Device::Device(const DeviceProps& deviceProps)
    : Device(deviceProps.physicalDevice, deviceProps.physicalDeviceFeatures, deviceProps.queueFlagBits) {}

    Device::~Device() {
        vkDeviceWaitIdle(GetDevice());
        vkDestroyDevice(GetDevice(), nullptr);
        VAS_LOG("device destroyed");
    }

    VkDevice Device::GetDevice() {
        if(m_device != VK_NULL_HANDLE) {
            return m_device;
        } else {
            VAS_LOG("accessing device while being undefined");
            return nullptr;
        }
    }
};