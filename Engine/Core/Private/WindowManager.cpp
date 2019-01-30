#include "WindowManager.hpp"

namespace dusk {

NullWindowManager NULL_WINDOW_MANAGER;

WindowManager * WindowManager::s_Inst = &NULL_WINDOW_MANAGER;

WindowManager * WindowManager::Inst()
{
    return s_Inst;
}

WindowManager::WindowManager()
{
    s_Inst = this;
}

WindowManager::~WindowManager()
{
    s_Inst = &NULL_WINDOW_MANAGER;
}

WindowHandle NullWindowManager::Open(const wstring& title, const ivec2& size)
{
    return 0;
}

bool NullWindowManager::Close(WindowHandle handle)
{
    return true;
}

void NullWindowManager::PollEvents()
{ }

void NullWindowManager::SwapBuffers(WindowHandle handle)
{ }

size_t NullWindowManager::Count() const
{
    return 0;
}

} // namespace dusk