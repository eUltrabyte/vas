#include "Device.hpp"

namespace vas {
    Device::Device() { }
    
    Device::Device(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures physicalDeviceFeatures, VkQueueFlagBits queueFlagBits)
    : m_queueFamilyIndex(-1), m_queueCount(1) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for(int i = 0; i < queueFamilies.size(); ++i) {
            if(queueFamilies[i].queueFlags & queueFlagBits) {
                VAS_LOG("queue family - " + std::to_string(i));
                m_queueFamilyIndex = i;

                if(queueFamilies[i].queueCount > m_queueCount) {
                    m_queueCount = 2;
                }

                break;
            }
        }

        if(m_queueFamilyIndex == -1) {
            VAS_LOG("none of queue families are suitable, using first available");
            m_queueFamilyIndex = 0;
        }

        VAS_LOG("queue count - " + std::to_string(m_queueCount));

        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo deviceQueueCreateInfo { };
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pNext = nullptr;
        deviceQueueCreateInfo.flags = 0;
        deviceQueueCreateInfo.queueCount = m_queueCount;
        deviceQueueCreateInfo.queueFamilyIndex = m_queueFamilyIndex;
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

    uint32_t& Device::GetQueueFamilyIndex() {
        return m_queueFamilyIndex;
    }
    
    uint32_t& Device::GetQueueCount() {
        return m_queueCount;
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