#define VK_USE_PLATFORM_XCB_KHR
#include <vas/vas.hpp>

#include <xcb/xcb.h>
#include <xcb/xproto.h>

auto main(int argc, char** argv) -> int {
    std::vector<const char*> instanceExtensions = {
        "VK_KHR_surface",
        "VK_KHR_xcb_surface"
    };

    std::unique_ptr<vas::Instance> instance = std::make_unique<vas::Instance>("App", std::span<const char*>(instanceExtensions), std::span<const char*>(), vas::InstanceVersion::VulkanAvailable, true, true);
    
    std::unique_ptr<vas::PhysicalDevice> physicalDevice = std::make_unique<vas::PhysicalDevice>(instance->GetInstance());

    std::vector<const char*> deviceExtensions = {
        "VK_KHR_swapchain"
    };

    std::unique_ptr<vas::Device> device = std::make_unique<vas::Device>(physicalDevice->GetPhysicalDevice(), physicalDevice->GetPhysicalDeviceFeatures(), VK_QUEUE_GRAPHICS_BIT, std::span<const char*>(deviceExtensions));

    std::unique_ptr<vas::QueueFamily> queueFamily = std::make_unique<vas::QueueFamily>(device->GetDevice(), device->GetQueueFamilyIndex(), device->GetQueueCount());

    xcb_connection_t* connection = xcb_connect(0, 0);
    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;

    xcb_window_t window = xcb_generate_id (connection);
    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 640, 360, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, 0);
    xcb_map_window(connection, window);
    xcb_flush(connection);

    VkSurfaceKHR surface;

    VkXcbSurfaceCreateInfoKHR xcbSurfaceCreateInfo { };
    xcbSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    xcbSurfaceCreateInfo.pNext = nullptr;
    xcbSurfaceCreateInfo.flags = 0;
    xcbSurfaceCreateInfo.connection = connection;
    xcbSurfaceCreateInfo.window = window;

    VAS_ASSERT(vkCreateXcbSurfaceKHR(instance->GetInstance(), &xcbSurfaceCreateInfo, nullptr, &surface));

    std::unique_ptr<vas::Swapchain> swapchain = std::make_unique<vas::Swapchain>(physicalDevice->GetPhysicalDevice(), device->GetDevice(), surface, VkExtent2D { 640, 360 });

    std::cin.get();
    swapchain.reset();
    vkDestroySurfaceKHR(instance->GetInstance(), surface, nullptr);
    xcb_disconnect(connection);
    return 0;
}