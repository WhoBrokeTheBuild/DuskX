#include "SDL2WindowManager.hpp"

#include <StringUtil.hpp>

#include <SDL_syswm.h>

#if defined(DUSK_GRAPHICS_OPENGL)
#include <SDL_opengl.h>
#elif defined(DUSK_GRAPHICS_VULKAN)
#include <SDL_vulkan.h>
#endif

namespace dusk {

SDL2WindowManager::SDL2WindowManager()
    : WindowManager()
{
    memset(_Windows, 0, sizeof(_Windows));

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL2\n");
    }

    SDL_version version;
    SDL_GetVersion(&version);
    printf("SDL Version: %d.%d.%d\n", (int)version.major, (int)version.minor, (int)version.patch);
}

SDL2WindowManager::~SDL2WindowManager()
{
    SDL_Window * window;

    for (int index = 0; index < MAX_WINDOWS; ++index) {
        if (!_Windows[index]) {
            continue;
        }

        SDL_GL_DeleteContext(_Contexts[index]);

        SDL_DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
    }

    SDL_Quit();
}

WindowHandle SDL2WindowManager::Open(const wstring& title, const ivec2& size)
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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, DUSK_OPENGL_VERSION_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, DUSK_OPENGL_VERSION_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

#endif

    string asciiTitle = WStringToString(title) + " (SDL2)";

    _Windows[index] = SDL_CreateWindow(
        asciiTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        size.x,
        size.y,
        0
#if defined(DUSK_GRAPHICS_OPENGL)
        | SDL_WINDOW_OPENGL
#elif defined(DUSK_GRAPHICS_VULKAN)
        | SDL_WINDOW_VULKAN
#endif
    );

    if (!_Windows[index]) {
        fprintf(stderr, "Failed to create SDL2 window\n");

        return 0;
    }


    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(_Windows[index], &info);

    printf("Window Manager: ");
    switch (info.subsystem) {
    case SDL_SYSWM_X11:
        printf("X11\n");
        break;
    case SDL_SYSWM_WAYLAND:
        printf("Wayland\n");
        break;
    case SDL_SYSWM_WINDOWS:
        printf("Windows\n");
        break;
    case SDL_SYSWM_WINRT:
        printf("WinRT\n");
        break;
    case SDL_SYSWM_COCOA:
        printf("OSX\n");
        break;
    case SDL_SYSWM_ANDROID:
        printf("Android\n");
        break;
    default:
        printf("Unknown\n");
    }

#if defined(DUSK_GRAPHICS_OPENGL)

    _Contexts[index] = SDL_GL_CreateContext(_Windows[index]);

    if (!_Contexts[index]) {
        fprintf(stderr, "Failed to create OpenGL context\n");

        SDL_DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

    if (!OpenGLInit()) {
        SDL_DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

#elif defined(DUSK_GRAPHICS_VULKAN)

    if (!VulkanInit()) {
        SDL_DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

#elif defined(DUSK_GRAPHICS_DIRECTX)

    if (!DirectXInit(info.info.win.window)) {
        SDL_DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

#endif

    ++_WindowCount;

    return index + 1;
}

bool SDL2WindowManager::Close(WindowHandle handle)
{
    int index = handle - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return false;
    }

    if (!_Windows[index]) {
        return false;
    }

#if defined(DUSK_GRAPHICS_OPENGL)

    SDL_GL_DeleteContext(_Contexts[index]);
    _Contexts[index] = nullptr;

#endif

    SDL_DestroyWindow(_Windows[index]);
    _Windows[index] = nullptr;

    --_WindowCount;

    return true;
}

void SDL2WindowManager::PollEvents()
{
    static SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_WINDOWEVENT) {
            switch (evt.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                for (int index = 0; index < MAX_WINDOWS; ++index) {
                    if (_Windows[index]) {
                        if (evt.window.windowID == SDL_GetWindowID(_Windows[index])) {
                            Close(index + 1);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}

void SDL2WindowManager::SwapBuffers(WindowHandle handle)
{
    int index = handle - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return;
    }

    if (!_Windows[index]) {
        return;
    }

    SDL_GL_SwapWindow(_Windows[index]);
}

size_t SDL2WindowManager::Count() const
{
    return _WindowCount;
}

#if defined(DUSK_GRAPHICS_OPENGL)

GLADloadfunc SDL2WindowManager::GetOpenGLLoadFunc() const
{
    return (GLADloadfunc)SDL_GL_GetProcAddress;
}

#elif defined(DUSK_GRAPHICS_VULKAN)

const char ** SDL2WindowManager::GetVulkanRequiredExtensions(uint32_t & count) const
{
    static const char * extensions[64];
    count = sizeof(extensions) / sizeof(extensions[0]);

    // FIXME: Get main window
    int index = 0;

    if (index < 0 || index >= MAX_WINDOWS) {
        return nullptr;
    }

    if (_Windows[index]) {
        SDL_bool result = SDL_Vulkan_GetInstanceExtensions(_Windows[index], &count, extensions);
        if (!result) {
            fprintf(stderr, "SDL_Vulkan_GetInstanceExtensions failed: %s\n", SDL_GetError());
            return nullptr;
        }
        return extensions;
    }

    return nullptr;
}

bool SDL2WindowManager::CreateVulkanWindowSurface(
    VkInstance instance,
    WindowHandle window,
    VkSurfaceKHR * surface)
{
    int index = window - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return false;
    }

    if (_Windows[index]) {
        SDL_bool result = SDL_Vulkan_CreateSurface(_Windows[index], instance, surface);
        if (!result) {
            fprintf(stderr, "SDL_CreateVulkanSurface failed: %s\n", SDL_GetError());
        }
        return (result == SDL_TRUE);
    }

    return false;
}

#endif

} // namespace dusk
