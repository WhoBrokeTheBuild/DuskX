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
    return L"";
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
    return "";
#endif
}

}
