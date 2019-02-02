#include "DirectX.hpp"

#include <stdio.h>
#include <tchar.h>
#include <dxdiag.h>

namespace dusk {

/**
 * Get the DirectX version string
 *
 * Adapted from GetDXVer.cpp
 * (C) Copyright Microsoft Corp.  All rights reserved.
 *
 * @param  strDirectXVersion  The buffer to store the version string in. Should be at least 10 characters.
 * @param  cchDirectXVersion  The size of strDirectXVersion.
 *
 * @return S_OK if the version was found, E_FAIL otherwise.
 */
HRESULT GetDXVersion(TCHAR* strDirectXVersion, int cchDirectXVersion)
{
    // Init values to unknown
    if (strDirectXVersion && cchDirectXVersion > 0) {
        strDirectXVersion[0] = 0;
    }

    DWORD dwDirectXVersionMajor = 0;
    DWORD dwDirectXVersionMinor = 0;
    TCHAR cDirectXVersionLetter = ' ';

    HRESULT hr;
    bool bCleanupCOM = false;

    bool bSuccessGettingMajor = false;
    bool bSuccessGettingMinor = false;
    bool bSuccessGettingLetter = false;

    // Init COM.  COM may fail if its already been inited with a different
    // concurrency model.  And if it fails you shouldn't release it.
    hr = CoInitialize(NULL);
    bCleanupCOM = SUCCEEDED(hr);

    // Get an IDxDiagProvider
    bool bGotDirectXVersion = false;
    IDxDiagProvider* pDxDiagProvider = NULL;
    hr = CoCreateInstance(
        CLSID_DxDiagProvider,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IDxDiagProvider,
        (LPVOID*)&pDxDiagProvider
    );

    if (SUCCEEDED(hr)) {
        DXDIAG_INIT_PARAMS dxDiagInitParam;
        ZeroMemory(&dxDiagInitParam, sizeof(DXDIAG_INIT_PARAMS));
        dxDiagInitParam.dwSize = sizeof(DXDIAG_INIT_PARAMS);
        dxDiagInitParam.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
        dxDiagInitParam.bAllowWHQLChecks = false;
        dxDiagInitParam.pReserved = NULL;

        hr = pDxDiagProvider->Initialize(&dxDiagInitParam);
        if (SUCCEEDED(hr)) {
            IDxDiagContainer* pDxDiagRoot = NULL;
            IDxDiagContainer* pDxDiagSystemInfo = NULL;

            hr = pDxDiagProvider->GetRootContainer(&pDxDiagRoot);
            if (SUCCEEDED(hr)) {
                hr = pDxDiagRoot->GetChildContainer(L"DxDiag_SystemInfo", &pDxDiagSystemInfo);
                if (SUCCEEDED(hr)) {
                    VARIANT var;
                    VariantInit(&var);

                    hr = pDxDiagSystemInfo->GetProp(L"dwDirectXVersionMajor", &var);
                    if (SUCCEEDED(hr) && var.vt == VT_UI4) {
                        dwDirectXVersionMajor = var.ulVal;
                        bSuccessGettingMajor = true;
                    }
                    VariantClear(&var);

                    hr = pDxDiagSystemInfo->GetProp(L"dwDirectXVersionMinor", &var);
                    if (SUCCEEDED(hr) && var.vt == VT_UI4) {
                        dwDirectXVersionMinor = var.ulVal;
                        bSuccessGettingMinor = true;
                    }
                    VariantClear(&var);

                    hr = pDxDiagSystemInfo->GetProp(L"szDirectXVersionLetter", &var);
                    if (SUCCEEDED(hr) && var.vt == VT_BSTR && SysStringLen(var.bstrVal) != 0) {
                        char strDestination[10];
                        WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1, strDestination, 10 * sizeof(CHAR), NULL, NULL);
                        cDirectXVersionLetter = (char)tolower(strDestination[0]);
                        bSuccessGettingLetter = true;
                    }
                    VariantClear(&var);

                    // If it all worked right, then mark it down
                    if (bSuccessGettingMajor && bSuccessGettingMinor && bSuccessGettingLetter) {
                        bGotDirectXVersion = true;
                    }

                    pDxDiagSystemInfo->Release();
                }

                pDxDiagRoot->Release();
            }
        }

        pDxDiagProvider->Release();
    }

    if (bCleanupCOM) {
        CoUninitialize();
    }

    if (!bGotDirectXVersion) {
        return E_FAIL;
    }

    if (strDirectXVersion && cchDirectXVersion > 0) {
        _sntprintf_s(strDirectXVersion, cchDirectXVersion, _TRUNCATE, TEXT("%d.%d%c"), dwDirectXVersionMajor, dwDirectXVersionMinor, cDirectXVersionLetter);
        strDirectXVersion[cchDirectXVersion - 1] = 0;
    }

    return S_OK;
}

} // namespace dusk
