#ifndef DUSK_SDL2_WINDOW_HPP
#define DUSK_SDL2_WINDOW_HPP

#include <WindowManager.hpp>
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

    size_t Count() const override;

private:

    static const int MAX_WINDOWS = 32;

    size_t _WindowCount = 0;

    WindowHandle _Handles[MAX_WINDOWS];

    SDL_GLContext _Contexts[MAX_WINDOWS];

}; // class SDL2Window

} // namespace dusk

#endif // DUSK_SDL2_WINDOW_HPP
