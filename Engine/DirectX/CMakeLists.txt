
SET(_TARGET DuskDirectX)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        DuskUtil
        d3d12.lib
        dxgi.lib
        d3dcompiler.lib
)

TARGET_COMPILE_DEFINITIONS(
    ${_TARGET}
    PUBLIC
        -DDUSK_GRAPHICS_DIRECTX
)
