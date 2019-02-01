
SET(_TARGET DuskSDL2)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        DuskCore
        DuskUtil
        SDL2::SDL2
        ${DUSK_GRAPHICS_LIBRARY}
    INTERFACE
        SDL2::SDL2main
)

TARGET_COMPILE_DEFINITIONS(
    ${_TARGET}
    PUBLIC
        -DDUSK_WINDOW_SDL2
)

TARGET_LINK_LIBRARIES(
    DuskCore
    PUBLIC
        ${_TARGET}
)