#include "WindowManager.hpp"

namespace dusk {

NullWindowManager NULL_WINDOW_MANAGER;

WindowManager * WindowManager::s_Inst = &NULL_WINDOW_MANAGER;

WindowManager * WindowManager::Inst()
{
    return s_Inst;
}

WindowManager::WindowManager()
{
    s_Inst = this;
}

WindowManager::~WindowManager()
{
    s_Inst = &NULL_WINDOW_MANAGER;
}

WindowHandle NullWindowManager::Open(const wstring& title, const ivec2& size)
{
    return 0;
}

bool NullWindowManager::Close(WindowHandle handle)
{
    return true;
}

void NullWindowManager::PollEvents()
{ }

void NullWindowManager::SwapBuffers(WindowHandle handle)
{ }

size_t NullWindowManager::Count() const
{
    return 0;
}

#if defined(DUSK_GRAPHICS_OPENGL)

void * NullGetProcAddress(const char *)
{
    return nullptr;
}

GLADloadfunc NullWindowManager::GetOpenGLLoadFunc() const
{
    return (GLADloadfunc)NullGetProcAddress;
}

#elif defined(DUSK_GRAPHICS_VULKAN)

const char ** NullWindowManager::GetVulkanRequiredExtensions(uint32_t & count) const
{
    count = 0;
    return nullptr;
}

bool NullWindowManager::CreateVulkanWindowSurface(
    VkInstance instance,
    WindowHandle window,
    VkSurfaceKHR * surface)
{
    surface = nullptr;
    return false;
}

#endif

} // namespace dusk