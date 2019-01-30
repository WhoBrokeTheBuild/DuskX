#ifndef DUSK_GLFW_WINDOW_MANAGER_HPP
#define DUSK_GLFW_WINDOW_MANAGER_HPP

#include <WindowManager.hpp>

#if defined(DUSK_GRAPHICS_OPENGL)
#include <OpenGL.hpp>
#elif defined(DUSK_GRAPHICS_VULKAN)
#include <Vulkan.hpp>
#elif defined(DUSK_GRAPHICS_DIRECTX)
#include <DirectX.hpp>
#endif

#include <GLFW\glfw3.h>

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

private:

    static const int MAX_WINDOWS = 32;

    size_t _WindowCount = 0;

    GLFWwindow * _Windows[MAX_WINDOWS];

}; // GLFWWindowManager

} // namespace dusk

#endif // DUSK_GLFW_WINDOW_MANAGER_HPP
