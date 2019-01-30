#ifndef DUSK_GRAPHICS_VULKAN_HPP
#define DUSK_GRAPHICS_VULKAN_HPP

#include <glad/vulkan.h>

namespace dusk {

void VulkanInit(const char ** requiredExtensions, uint32_t requiredExtensionCount);

VkInstance VulkanGetInstance();

} // namespace dusk

#endif // DUSK_GRAPHICS_VULKAN_HPP
