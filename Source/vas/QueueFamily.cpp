#include "QueueFamily.hpp"

namespace vas {
    QueueFamily::QueueFamily() { }

    QueueFamily::QueueFamily(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueCount) {
        vkGetDeviceQueue(device, queueFamilyIndex, 0, &m_graphicsQueue);

        if(queueCount > 1) {
            vkGetDeviceQueue(device, queueFamilyIndex, queueCount - 1, &m_presentQueue);
        } else {
            m_graphicsQueue = m_presentQueue;
        }

        VAS_LOG("graphics queue index - " + std::to_string(0));
        VAS_LOG("present queue index - " + std::to_string(queueCount - 1));
    }

    QueueFamily::QueueFamily(const QueueFamilyProps& queueFamilyProps)
    : QueueFamily(queueFamilyProps.device, queueFamilyProps.queueFamilyIndex, queueFamilyProps.queueCount) { }

    VkQueue& QueueFamily::GetGraphicsQueue() {
        return m_graphicsQueue;
    }
    
    VkQueue& QueueFamily::GetPresentQueue() {
        return m_presentQueue;
    }
};