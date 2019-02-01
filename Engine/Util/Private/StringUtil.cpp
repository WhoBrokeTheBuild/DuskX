#include "StringUtil.hpp"

#include <Platform.hpp>

namespace dusk {

wstring StringToWString(const string& str)
{
#if defined(_WIN32)
    int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, NULL);

    wstring result;
    result.resize(length);

    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), result.data(), (int)result.size());

    return result;
#else
    size_t length = std::mbstowcs(nullptr, str.c_str(), 0);

    wstring result;
    result.resize(length);

    std::mbstowcs(result.data(), str.c_str(), (int)result.size());

    return result;
#endif
}

string WStringToString(const std::wstring& wstr)
{
#if defined(_WIN32)
    int length = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, NULL, NULL, NULL);

    string result;
    result.resize(length);

    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), result.data(), (int)result.size(), NULL, NULL);

    return result;
#else
    std::mbstate_t state = std::mbstate_t();
    const wchar_t * wptr = wstr.c_str();

    size_t length = std::wcsrtombs(nullptr, &wptr, 0, &state);

    string result;
    result.resize(length);

    std::wcsrtombs(result.data(), &wptr, (int)result.size(), &state);

    return result;
#endif
}

}
