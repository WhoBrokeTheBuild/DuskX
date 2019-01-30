#include <SDL2WindowManager.hpp>

using namespace std;
using namespace dusk;

int main(int argc, char ** argv) 
{
    auto sdl2wm = new SDL2WindowManager();
    auto wm = WindowManager::Inst();

    WindowHandle h1 = wm->Open(L"Demo", ivec2(1024, 768));
    WindowHandle h2 = wm->Open(L"Hi Tom", ivec2(300, 300));

    while (wm->Count()) {
        wm->PollEvents();
    }

    wm->Close(h2);
    wm->Close(h1);

    delete sdl2wm;

    return 0;
}