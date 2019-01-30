#include "Vulkan.hpp"

#include <vector>

namespace dusk {

VkInstance instance;
VkSurfaceKHR windowSurface;
VkPhysicalDevice physicalDevice;
VkDevice device;
VkQueue graphicsQueue;
VkQueue presentQueue;
VkSemaphore imageAvailableSemaphore;
VkSemaphore renderingFinishedSemaphore;
VkSwapchainKHR swapChain;
std::vector<VkImage> swapChainImages;
VkCommandPool commandPool;
std::vector<VkCommandBuffer> presentCommandBuffers;

void VulkanInit(const char ** requiredExtensions, uint32_t requiredExtensionCount)
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Dusk";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Dusk";
    appInfo.engineVersion = VK_MAKE_VERSION(
        DUSK_VERSION_MAJOR,
        DUSK_VERSION_MINOR,
        DUSK_VERSION_PATCH);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    uint32_t availableExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, availableExtensions.data());

    printf("Vulkan Extensions:\n");
    for (const auto& extension : availableExtensions) {
        printf("\t%s\n", extension.extensionName);
    }

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = requiredExtensionCount;
    createInfo.ppEnabledExtensionNames = requiredExtensions;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan instance\n");
        return;
    }
}

VkInstance VulkanGetInstance()
{
    return instance;
}

void VulkanRender()
{

}

} // namespace dusk
