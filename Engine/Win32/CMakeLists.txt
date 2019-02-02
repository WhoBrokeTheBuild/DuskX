
SET(_TARGET DuskWin32)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        DuskCore
        DuskUtil
        ${DUSK_GRAPHICS_LIBRARY}
        $<$<CXX_COMPILER_ID:MSVC>:msvcrt>
)

TARGET_COMPILE_DEFINITIONS(
    ${_TARGET}
    PUBLIC
        -DDUSK_WINDOW_WIN32
)

TARGET_LINK_LIBRARIES(
    DuskCore
    PUBLIC
        ${_TARGET}
)
