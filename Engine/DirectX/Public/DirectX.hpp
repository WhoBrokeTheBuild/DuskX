#ifndef DUSK_GRAPHICS_OPENGL_HPP
#define DUSK_GRAPHICS_OPENGL_HPP

#define INITGUID
#include <Platform.hpp>

namespace dusk {

bool DirectXInit(HWND hwnd);

HRESULT GetDXVersion(TCHAR* strDirectXVersion, int cchDirectXVersion);

} // namespace dusk

#endif // DUSK_GRAPHICS_OPENGL_HPP
