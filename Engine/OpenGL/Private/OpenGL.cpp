#include "OpenGL.hpp"

#include <WindowManager.hpp>

#include <stdio.h>

namespace dusk {

bool OpenGLInit()
{
    auto wm = WindowManager::Inst();
    int version = gladLoadGL(wm->GetOpenGLLoadFunc());
    if (!version) {
        fprintf(stderr, "Failed to load OpenGL symbols\n");
        return false;
    }

    printf("OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glClearColor(0.3f, 0.0f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    return true;
}

} // namespace dusk
