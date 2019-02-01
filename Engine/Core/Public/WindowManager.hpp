#ifndef DUSK_WINDOW_MANAGER_HPP
#define DUSK_WINDOW_MANAGER_HPP

#if defined(DUSK_GRAPHICS_OPENGL)
#include <OpenGL.hpp>
#elif defined(DUSK_GRAPHICS_VULKAN)
#include <Vulkan.hpp>
#elif defined(DUSK_GRAPHICS_DIRECTX)
#include <DirectX.hpp>
#endif

#include <Math.hpp>

#include <cstdint>
#include <string>

namespace dusk {

using std::wstring;

typedef uint32_t WindowHandle;

class App;

class WindowManager
{
    friend class App;

public:

    /**
     * Disable Copy Constructor and Assignment Operator
     */
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    /**
     * Return an instance to the current window manager.
     *
     * @return The current window manager, or nullptr.
     */
    static WindowManager * Inst();

    /**
     * Open a new window, and return it's handle.
     *
     * @param  title  The title for the new window.
     * @param  size   The size in pixels for the new window.
     *
     * @return A handle to the new window.
     */
    virtual WindowHandle Open(const wstring& title, const ivec2& size) = 0;

    /**
     * Close a window.
     *
     * @param  window  A handle to the window to close.
     */
    virtual bool Close(WindowHandle handle) = 0;

    /**
     * Poll for new events and dispatch event handlers.
     */
    virtual void PollEvents() = 0;

    /**
    * Swap the back and front buffers.
    */
    virtual void SwapBuffers(WindowHandle handle) = 0;

    /**
     * Return the number of open windows.
     *
     * @return The number of open windows.
     */
    virtual size_t Count() const = 0;

#if defined(DUSK_GRAPHICS_OPENGL)

    virtual GLADloadfunc GetOpenGLLoadFunc() const = 0;

#elif defined(DUSK_GRAPHICS_VULKAN)

    virtual const char ** GetVulkanRequiredExtensions(uint32_t & count) const = 0;

    virtual bool CreateVulkanWindowSurface(
        VkInstance instance,
        WindowHandle window,
        VkSurfaceKHR * surface) = 0;

#endif // DUSK_GRAPHICS_VULKAN

protected:

    WindowManager();

    virtual ~WindowManager();

private:

    static WindowManager * s_Inst;

}; // class WindowManager

class NullWindowManager final : public WindowManager
{
public:

    NullWindowManager() = default;

    ~NullWindowManager() = default;

    WindowHandle Open(const wstring& title, const ivec2& size) override;

    bool Close(WindowHandle handle) override;

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

}; // class NullWindowManager

} // namespace dusk

#endif // DUSK_WINDOW_MANAGER_HPP
