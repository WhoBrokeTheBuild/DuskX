#include "Win32WindowManager.hpp"

#include <App.hpp>
#include <StringUtil.hpp>

namespace dusk {

Win32WindowManager * _win32wm = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (_win32wm) {
        return _win32wm->HandleMessage(hwnd, msg, wParam, lParam);
    }
    return 0;
}

Win32WindowManager::Win32WindowManager()
{
    memset(_Windows, 0, sizeof(_Windows));
    _win32wm = this;
}

Win32WindowManager::~Win32WindowManager()
{
    _win32wm = nullptr;
}

WindowHandle Win32WindowManager::Open(const wstring& title, const ivec2& size)
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

    auto app = App::Inst();

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = app->GetName();
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        fprintf(stderr, "Failed to register Win32 window\n");
        return 0;
    }

    string asciiTitle = WStringToString(title) + " (Win32)";

    _Windows[index] = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        app->GetName(),
        asciiTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        size.x,
        size.y,
        NULL,
        NULL,
        (HINSTANCE)GetModuleHandle(NULL),
        NULL
    );

    if (!_Windows[index]) {
        fprintf(stderr, "Failed to create Win32 window\n");
        return 0;
    }

    ShowWindow(_Windows[index], SW_SHOWNORMAL);
    UpdateWindow(_Windows[index]);

    if (!DirectXInit(_Windows[index])) {
        DestroyWindow(_Windows[index]);
        _Windows[index] = nullptr;
        return 0;
    }

    ++_WindowCount;

    return index + 1;
}

bool Win32WindowManager::Close(WindowHandle handle)
{
    int index = handle - 1;

    if (index < 0 || index >= MAX_WINDOWS) {
        return false;
    }

    if (!_Windows[index]) {
        return false;
    }

    DestroyWindow(_Windows[index]);
    _Windows[index] = nullptr;

    --_WindowCount;

    return false;
}

void Win32WindowManager::PollEvents()
{
    MSG Msg;
    if (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

void Win32WindowManager::SwapBuffers(WindowHandle handle)
{

}

size_t Win32WindowManager::Count() const
{
    return _WindowCount;
}

LRESULT Win32WindowManager::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CLOSE:
        for (int index = 0; index < MAX_WINDOWS; ++index) {
            if (_Windows[index] == hwnd) {
                Close(index + 1);
                break;
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

} // namespace dusk
