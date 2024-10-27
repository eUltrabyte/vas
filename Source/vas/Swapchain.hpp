#pragma once
#ifndef VAS_SWAPCHAIN_HEADER
#define VAS_SWAPCHAIN_HEADER

#include "vas.hpp"

namespace vas {
    class VAS_API Swapchain {
    public:
        Swapchain(VkDevice device);
        virtual ~Swapchain();

        virtual VkSwapchainKHR GetSwapchain();

    protected:
        VkDevice p_device;

    private:
        VkSwapchainKHR m_swapchain;

    };
};

#endif