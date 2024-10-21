#include "PhysicalDevice.hpp"

namespace vas {
    PhysicalDevice::PhysicalDevice()
    : m_physicalDeviceProperties({ }), m_physicalDeviceFeatures({ }) { }

    PhysicalDevice::PhysicalDevice(VkInstance instance)
    : m_physicalDeviceProperties({ }), m_physicalDeviceFeatures({ }) {
        unsigned int physicalDevicesCount = 0;
        vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr);
        std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
        vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        std::vector<VkPhysicalDeviceProperties> physicalDevicesProperties(physicalDevicesCount);
        std::vector<VkPhysicalDeviceFeatures> physicalDevicesFeatures(physicalDevicesCount);

        bool found = false;
        for(auto i = 0; i < physicalDevices.size(); ++i) {
            vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDevicesProperties[i]);
            vkGetPhysicalDeviceFeatures(physicalDevices[i], &physicalDevicesFeatures[i]);

            if(physicalDevicesProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && physicalDevicesFeatures[i].geometryShader == VK_TRUE) {
                VAS_LOG("gpu - " + std::string(physicalDevicesProperties[i].deviceName));

                m_physicalDeviceProperties = physicalDevicesProperties[i];
                m_physicalDeviceFeatures = physicalDevicesFeatures[i];
                m_physicalDevice = physicalDevices[i];
                found = true;
            } else {
                VAS_LOG("gpu - " + std::to_string(i) + " - does not meet the criteria");
            }
        }

        if(!found) {
            m_physicalDeviceProperties = physicalDevicesProperties[0];
            m_physicalDeviceFeatures = physicalDevicesFeatures[0];
            m_physicalDevice = physicalDevices[0];
        }

        VAS_LOG("physical device is ready");
    }

    VkPhysicalDeviceProperties& PhysicalDevice::GetPhysicalDeviceProperties() {
        return m_physicalDeviceProperties;
    }
    
    VkPhysicalDeviceFeatures& PhysicalDevice::GetPhysicalDeviceFeatures() {
        return m_physicalDeviceFeatures;
    }
    
    VkPhysicalDevice PhysicalDevice::GetPhysicalDevice() {
        if(m_physicalDevice != VK_NULL_HANDLE) {
            return m_physicalDevice;
        } else {
            VAS_LOG("accessing physical device while being undefined");
            return nullptr;
        }
    }
};