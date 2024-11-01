#pragma once
#ifndef VAS_SWAPCHAIN_HEADER
#define VAS_SWAPCHAIN_HEADER

#include "vas.hpp"

namespace vas {
    class VAS_API Swapchain {
    public:
        Swapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, VkExtent2D extent);
        virtual ~Swapchain();

        virtual void Recreate(VkSurfaceKHR surface, VkExtent2D extent);

        virtual VkSwapchainKHR GetSwapchain();

    protected:
        VkDevice p_device;

    private:
        uint32_t m_imageCount;
        VkSurfaceFormatKHR m_surfaceFormat;
        VkPresentModeKHR m_presentMode;
        VkSurfaceCapabilitiesKHR m_surfaceCapabilities;
        VkSwapchainKHR m_swapchain;

    };
};

#endif