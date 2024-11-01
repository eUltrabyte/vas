#include "Swapchain.hpp"

namespace vas {
    Swapchain::Swapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, VkExtent2D extent)
    : p_device(device) {
        unsigned int surfaceFormatsCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatsCount, nullptr);
        std::vector<VkSurfaceFormatKHR> surfaceFormats = std::vector<VkSurfaceFormatKHR>(surfaceFormatsCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatsCount, surfaceFormats.data());
        
        for(auto surfaceFormat : surfaceFormats) {
            if(surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                m_surfaceFormat = surfaceFormat;
            }
        }

        if(m_surfaceFormat.format != VK_FORMAT_B8G8R8A8_SRGB && m_surfaceFormat.colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            m_surfaceFormat = surfaceFormats[0];
        }

        uint32_t presentModesCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModesCount, nullptr);
        std::vector<VkPresentModeKHR> presentModes = std::vector<VkPresentModeKHR>(presentModesCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModesCount, presentModes.data());

        for(auto presentMode : presentModes) {
            if(presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                m_presentMode = presentMode;
            }
        }

        if(m_presentMode != VK_PRESENT_MODE_MAILBOX_KHR) {
            m_presentMode = VK_PRESENT_MODE_FIFO_KHR;
        }

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &m_surfaceCapabilities);

        m_imageCount = m_surfaceCapabilities.minImageCount + 1;
        if(m_surfaceCapabilities.maxImageCount > 0 && m_imageCount > m_surfaceCapabilities.maxImageCount) {
            m_imageCount = m_surfaceCapabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swapchainCreateInfo { };
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.flags = 0;
        swapchainCreateInfo.minImageCount = m_imageCount;
        swapchainCreateInfo.imageFormat = m_surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = m_surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        swapchainCreateInfo.preTransform = m_surfaceCapabilities.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = m_presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.surface = surface;
        swapchainCreateInfo.oldSwapchain = nullptr;

        VAS_ASSERT(vkCreateSwapchainKHR(p_device, &swapchainCreateInfo, nullptr, &m_swapchain));

        VAS_LOG("swapchain created");
    }

    Swapchain::~Swapchain() {
        vkDestroySwapchainKHR(p_device, GetSwapchain(), nullptr);
        VAS_LOG("swapchain destroyed");
    }

    void Swapchain::Recreate(VkSurfaceKHR surface, VkExtent2D extent) {
        VkSwapchainCreateInfoKHR swapchainCreateInfo { };
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.flags = 0;
        swapchainCreateInfo.minImageCount = m_imageCount;
        swapchainCreateInfo.imageFormat = m_surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = m_surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        swapchainCreateInfo.preTransform = m_surfaceCapabilities.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = m_presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.surface = surface;
        swapchainCreateInfo.oldSwapchain = m_swapchain;

        VAS_ASSERT(vkCreateSwapchainKHR(p_device, &swapchainCreateInfo, nullptr, &m_swapchain));

        VAS_LOG("swapchain recreated");
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