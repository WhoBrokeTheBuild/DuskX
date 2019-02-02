#include "App.hpp"

#if defined(DUSK_WINDOW_SDL2)
#include <SDL2WindowManager.hpp>
#elif defined(DUSK_WINDOW_GLFW)
#include <GLFWWindowManager.hpp>
#endif

namespace dusk {

App * App::s_Inst = nullptr;

App * App::Inst()
{
    return s_Inst;
}

App::App()
{
    s_Inst = this;
}

App::~App()
{
    s_Inst = nullptr;
}

void App::SetName(const char * name)
{
    _Name = name;
}

void App::SetVersion(const char * version)
{
    _Version = version;

    sscanf(_Version, "%d.%d.%d", &_VersionMajor, &_VersionMinor, &_VersionPatch);
}

bool App::Init()
{
    printf("Initializing %s version %s\n", GetName(), GetVersion());

#if defined(DUSK_WINDOW_SDL2)
    _WindowManager = new SDL2WindowManager();
#elif defined(DUSK_WINDOW_GLFW)
    _WindowManager = new GLFWWindowManager();
#endif

    return true;
}

void App::Term()
{
    delete _WindowManager;
    _WindowManager = nullptr;
}

const char * App::GetName() const
{
    return _Name;
}

const char * App::GetVersion() const
{
    return _Version;
}

int App::GetVersionMajor() const
{
    return _VersionMajor;
}

int App::GetVersionMinor() const
{
    return _VersionMinor;
}

int App::GetVersionPatch() const
{
    return _VersionPatch;
}

} // namespace dusk