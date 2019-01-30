#if defined(DUSK_WINDOW_SDL2)
#include <SDL2WindowManager.hpp>
#elif defined(DUSK_WINDOW_GLFW)
#include <GLFWWindowManager.hpp>
#endif

#include <WindowManager.hpp>

using namespace std;
using namespace dusk;

int main(int argc, char ** argv) 
{
#if defined(DUSK_WINDOW_SDL2)
    auto syswm = new SDL2WindowManager();
#elif defined(DUSK_WINDOW_GLFW)
    auto syswm = new GLFWWindowManager();
#else
	void * syswm = nullptr;
#endif

    auto wm = WindowManager::Inst();

    WindowHandle h = wm->Open(L"Demo", ivec2(1024, 768));

    while (wm->Count()) {
        wm->PollEvents();
		wm->SwapBuffers(h);
    }

	delete syswm;

    return 0;
}
