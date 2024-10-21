#pragma once
#ifndef VAS_QUEUE_FAMILY_HEADER
#define VAS_QUEUE_FAMILY_HEADER

#include "vas.hpp"

namespace vas {
    struct VAS_API QueueFamilyProps {
        QueueFamilyProps(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueCount) 
        : device(device), queueFamilyIndex(queueFamilyIndex), queueCount(queueCount) { }
        ~QueueFamilyProps() = default;

        VkDevice device;
        uint32_t queueFamilyIndex;
        uint32_t queueCount;
    };

    class VAS_API QueueFamily {
    public:
        QueueFamily();
        QueueFamily(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueCount);
        QueueFamily(const QueueFamilyProps& queueFamilyProps);
        virtual ~QueueFamily() = default;

        virtual VkQueue& GetGraphicsQueue();
        virtual VkQueue& GetPresentQueue();

    private:
        VkQueue m_graphicsQueue;
        VkQueue m_presentQueue;

    };
};

#endif