
SET(_TARGET DuskGLFW)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        DuskCore
        DuskUtil
        glfw
        ${DUSK_GRAPHICS_LIBRARY}
        $<$<CXX_COMPILER_ID:MSVC>:msvcrt>
)

TARGET_COMPILE_DEFINITIONS(
    ${_TARGET}
    PUBLIC
        -DDUSK_WINDOW_GLFW
)

TARGET_LINK_LIBRARIES(
    DuskCore
    PUBLIC
        ${_TARGET}
)
