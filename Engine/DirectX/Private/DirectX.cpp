#include "DirectX.hpp"

#include <stdio.h>

namespace dusk {

bool DirectXInit(HWND hwnd)
{
    TCHAR strDirectXVersion[10];
    HRESULT hr = GetDXVersion(strDirectXVersion, sizeof(strDirectXVersion));
    if (SUCCEEDED(hr)) {
        printf("DirectX Version: %s\n", strDirectXVersion);
    }

    return true;
}

} // namespace dusk
