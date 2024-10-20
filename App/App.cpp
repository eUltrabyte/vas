#include <vas/vas.hpp>

auto main(int argc, char** argv) -> int {
    std::unique_ptr<vas::Instance> instance = std::make_unique<vas::Instance>("App", std::span<const char*>(), std::span<const char*>(), vas::InstanceVersion::VulkanAvailable, true, true);
    
    std::unique_ptr<vas::PhysicalDevice> physicalDevice = std::make_unique<vas::PhysicalDevice>(instance->GetInstance());

    std::unique_ptr<vas::Device> device = std::make_unique<vas::Device>(physicalDevice->GetPhysicalDevice(), physicalDevice->GetPhysicalDeviceFeatures());

    std::cin.get();
    return 0;
}