#include "Swapchain.hpp"

namespace vas {
    Swapchain::Swapchain(VkDevice device)
    : p_device(device) {

    }

    Swapchain::~Swapchain() {
        vkDestroySwapchainKHR(p_device, GetSwapchain(), nullptr);
    }

    VkSwapchainKHR Swapchain::GetSwapchain() {
        if(m_swapchain != VK_NULL_HANDLE) {
            return m_swapchain;
        } else {
            VAS_LOG("accessing swapchain while being undefined");
            return nullptr;
        }
    }
};