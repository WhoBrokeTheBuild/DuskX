#include "Vulkan.hpp"

#include <App.hpp>

#include <stdio.h>
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

bool VulkanInit()
{
    auto app = App::Inst();
    auto wm = WindowManager::Inst();

    int version = gladLoaderLoadVulkan(NULL, NULL, NULL);
    if (!version) {
        fprintf(stderr, "Failed to load Vulkan symbols\n");
        return false;
    }

    printf("Vulkan %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    VkApplicationInfo appInfo = { };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = app->GetName();
    appInfo.applicationVersion = VK_MAKE_VERSION(
        app->GetVersionMajor(),
        app->GetVersionMinor(),
        app->GetVersionPatch());
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

    uint32_t requiredExtensionCount;
    const char ** requiredExtensions = wm->GetVulkanRequiredExtensions(requiredExtensionCount);

    VkInstanceCreateInfo createInfo = { };
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = requiredExtensionCount;
    createInfo.ppEnabledExtensionNames = requiredExtensions;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan instance\n");
        return false;
    }

    if (!wm->CreateVulkanWindowSurface(instance, 1, &windowSurface) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan window surface\n");
        return false;
    }

    return true;
}

} // namespace dusk
