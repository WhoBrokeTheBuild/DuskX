#include "GLFWWindowManager.hpp"

#include <StringUtil.hpp>
#include <vector>

namespace dusk {

void _WindowCloseCallback(GLFWwindow * window)
{
    GLFWWindowManager * wm = (GLFWWindowManager *)glfwGetWindowUserPointer(window);
    wm->Close(wm->GetHandle(window));
}

GLFWWindowManager::GLFWWindowManager()
{
    memset(_Windows, 0, sizeof(_Windows));

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }

    printf("GLFW Version: %s\n", glfwGetVersionString());
}

GLFWWindowManager::~GLFWWindowManager()
{
    for (int index = 0; index < MAX_WINDOWS; ++index) {
        if (_Windows[index]) {
            glfwDestroyWindow(_Windows[index]);
            _Windows[index] = nullptr;
        }
    }

    glfwTerminate();
}

WindowHandle GLFWWindowManager::Open(const wstring& title, const ivec2& size)
{
    int index = 0;
    for (; index < MAX_WINDOWS; ++index) {
        if (!_Windows[index]) {
            break;
        }
    }

    if (index == MAX_WINDOWS) {
        fprintf(stderr, "Maximum window count reached\n");
        return 0;
    }

#if defined(DUSK_GRAPHICS_OPENGL)

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DUSK_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DUSK_OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_SAMPLES, 4);

#elif defined(DUSK_GRAPHICS_VULKAN)

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

#endif

    string asciiTitle = WStringToString(title) + " (GLFW)";

    _Windows[index] = glfwCreateWindow(size.x, size.y, asciiTitle.c_str(), NULL, NULL);

    glfwMakeContextCurrent(_Windows[index]);

#if defined(DUSK_GRAPHICS_OPENGL)

    if (!OpenGLInit()) {
        glfwDestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

#elif defined(DUSK_GRAPHICS_VULKAN)

    if (!VulkanInit()) {
        glfwDestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

#endif

    ++_WindowCount;

    glfwSetWindowUserPointer(_Windows[index], this);

    glfwSetWindowCloseCallback(_Windows[index], _WindowCloseCallback);

    return index + 1;
}

bool GLFWWindowManager::Close(WindowHandle handle)
{
    int index = handle - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return false;
    }

    if (!_Windows[index]) {
        return false;
    }

    glfwDestroyWindow(_Windows[index]);
    _Windows[index] = nullptr;

    --_WindowCount;

    return true;
}

WindowHandle GLFWWindowManager::GetHandle(GLFWwindow * window)
{
    for (int index = 0; index < MAX_WINDOWS; ++index) {
        if (_Windows[index] == window) {
            return index + 1;
        }
    }

    return 0;
}

void GLFWWindowManager::PollEvents()
{
    glfwPollEvents();

    for (int index = 0; index < MAX_WINDOWS; ++index) {
        if (_Windows[index]) {
            if (glfwWindowShouldClose(_Windows[index])) {
                Close(index);
            }
        }
    }
}

void GLFWWindowManager::SwapBuffers(WindowHandle handle)
{
    int index = handle - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return;
    }

    if (_Windows[index]) {
        glfwSwapBuffers(_Windows[index]);
    }
}

size_t GLFWWindowManager::Count() const
{
    return _WindowCount;
}

#if defined(DUSK_GRAPHICS_OPENGL)

GLADloadfunc GLFWWindowManager::GetOpenGLLoadFunc() const
{
    return glfwGetProcAddress;
}

#elif defined(DUSK_GRAPHICS_VULKAN)

const char ** GLFWWindowManager::GetVulkanRequiredExtensions(uint32_t & count) const
{
    return glfwGetRequiredInstanceExtensions(&count);
}

bool GLFWWindowManager::CreateVulkanWindowSurface(
    VkInstance instance,
    WindowHandle window,
    VkSurfaceKHR * surface)
{
    int index = window - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return false;
    }

    if (_Windows[index]) {
        VkResult result = glfwCreateWindowSurface(instance, _Windows[index], nullptr, surface);
        return (result == VK_SUCCESS);
    }

    return false;
}

#endif

} // namespace dusk
