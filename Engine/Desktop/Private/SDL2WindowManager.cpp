#include "SDL2WindowManager.hpp"

#include <StringUtil.hpp>

namespace dusk {

SDL2WindowManager::SDL2WindowManager()
    : WindowManager()
{ 
    SDL_Init(SDL_INIT_VIDEO);
    memset(_Handles, 0, sizeof(_Handles));
}

SDL2WindowManager::~SDL2WindowManager()
{
    SDL_Window * window;

    for (int index = 0; index < MAX_WINDOWS; ++index) {
        if (!_Handles[index]) {
            break;
        }

        SDL_GL_DeleteContext(_Contexts[index]);

        window = SDL_GetWindowFromID(_Handles[index]);
        if (window) {
            SDL_DestroyWindow(window);
        }
    }

    SDL_Quit();
}

WindowHandle SDL2WindowManager::Open(const wstring& title, const ivec2& size)
{
    int index = 0;
    for (; index < MAX_WINDOWS; ++index) {
        if (!_Handles[index]) {
            break;
        }
    }

    if (index == MAX_WINDOWS) {
        return 0;
    }

    string asciiTitle = WStringToString(title);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_Window * window = SDL_CreateWindow(
        asciiTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        size.x,
        size.y,
        SDL_WINDOW_OPENGL
    );

    _Contexts[index] = SDL_GL_CreateContext(window);

    _Handles[index] = SDL_GetWindowID(window);

    ++_WindowCount;

    return _Handles[index];
}

bool SDL2WindowManager::Close(WindowHandle handle)
{
    int index = 0;
    for (; index < MAX_WINDOWS; ++index) {
        if (_Handles[index] == handle) {
            break;
        }
    }

    if (index == MAX_WINDOWS) {
        return 0;
    }

    SDL_GL_DeleteContext(_Contexts[index]);
    _Contexts[index] = nullptr;

    SDL_Window * window = SDL_GetWindowFromID(handle);

    if (!window) {
        return false;
    }

    SDL_DestroyWindow(window);
    _Handles[index] = 0;

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
                Close(evt.window.windowID);
            }
        }
    }
}

size_t SDL2WindowManager::Count() const
{
    return _WindowCount;
}

} // namespace dusk