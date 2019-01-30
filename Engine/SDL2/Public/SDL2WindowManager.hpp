#ifndef DUSK_WINDOW_SDL2_WINDOW_HPP
#define DUSK_WINDOW_SDL2_WINDOW_HPP

#include <WindowManager.hpp>

#if defined(DUSK_GRAPHICS_OPENGL)
#include <OpenGL.hpp>
#elif defined(DUSK_GRAPHICS_VULKAN)
#include <Vulkan.hpp>
#elif defined(DUSK_GRAPHICS_DIRECTX)
#include <DirectX.hpp>
#endif

#include <SDL.h>

namespace dusk {

class SDL2WindowManager final : public WindowManager
{
public:

    SDL2WindowManager();

    ~SDL2WindowManager();

    WindowHandle Open(const wstring& title, const ivec2& size) override;

    bool Close(WindowHandle handle) override;

    void PollEvents() override;

	void SwapBuffers(WindowHandle handle) override;

    size_t Count() const override;

private:

    static const int MAX_WINDOWS = 32;

    size_t _WindowCount = 0;

    SDL_Window * _Windows[MAX_WINDOWS];

    SDL_GLContext _Contexts[MAX_WINDOWS];

}; // class SDL2Window

} // namespace dusk

#endif // DUSK_WINDOW_SDL2_WINDOW_HPP
