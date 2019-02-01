#ifndef DUSK_GLFW_WINDOW_MANAGER_HPP
#define DUSK_GLFW_WINDOW_MANAGER_HPP

#include <WindowManager.hpp>

#include <GLFW/glfw3.h>

namespace dusk {

class GLFWWindowManager final : public WindowManager
{
public:

    GLFWWindowManager();

    ~GLFWWindowManager();

    WindowHandle Open(const wstring& title, const ivec2& size) override;

    bool Close(WindowHandle handle) override;

    WindowHandle GetHandle(GLFWwindow * window);

    void PollEvents() override;

    void SwapBuffers(WindowHandle handle) override;

    size_t Count() const override;

#if defined(DUSK_GRAPHICS_OPENGL)

    GLADloadfunc GetOpenGLLoadFunc() const override;

#elif defined(DUSK_GRAPHICS_VULKAN)

    const char ** GetVulkanRequiredExtensions(uint32_t & count) const override;

    bool CreateVulkanWindowSurface(
        VkInstance instance,
        WindowHandle window,
        VkSurfaceKHR * surface) override;

#endif

private:

    static const int MAX_WINDOWS = 32;

    size_t _WindowCount = 0;

    GLFWwindow * _Windows[MAX_WINDOWS];

}; // GLFWWindowManager

} // namespace dusk

#endif // DUSK_GLFW_WINDOW_MANAGER_HPP
