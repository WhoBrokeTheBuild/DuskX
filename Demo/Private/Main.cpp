#include <App.hpp>

using namespace std;
using namespace dusk;

int main(int argc, char ** argv)
{
    dusk::App app;
    app.SetName(PROJECT_NAME);
    app.SetVersion(PROJECT_VERSION);
    app.Init();

    auto wm = WindowManager::Inst();

    WindowHandle h = wm->Open(L"Demo", ivec2(1024, 768));

    while (wm->Count()) {
        wm->PollEvents();
        wm->SwapBuffers(h);
    }

    app.Term();
    return 0;
}
