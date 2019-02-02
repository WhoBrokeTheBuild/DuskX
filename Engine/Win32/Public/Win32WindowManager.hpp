#ifndef DUSK_WIN32_WINDOW_MANAGER_HPP
#define DUSK_WIN32_WINDOW_MANAGER_HPP

#include <Platform.hpp>
#include <WindowManager.hpp>

namespace dusk {

class Win32WindowManager final : public WindowManager
{
public:

    Win32WindowManager();

    ~Win32WindowManager();

    WindowHandle Open(const wstring& title, const ivec2& size) override;

    bool Close(WindowHandle handle) override;

    void PollEvents() override;

    void SwapBuffers(WindowHandle handle) override;

    size_t Count() const override;

    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:

    static const int MAX_WINDOWS = 32;

    size_t _WindowCount = 0;

    HWND _Windows[MAX_WINDOWS];

}; // class Win32WindowManager

} // namespace dusk

#endif // DUSK_WIN32_WINDOW_MANAGER_HPP
