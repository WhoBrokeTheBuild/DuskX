#include "StringUtil.hpp"

#include <locale>
#include <codecvt>

namespace dusk {

wstring StringToWString(const std::string& str)
{
    using convertType = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convertType, wchar_t> converter;

    return converter.from_bytes(str);
}

string WStringToString(const std::wstring& wstr)
{
    using convertType = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convertType, wchar_t> converter;

    return converter.to_bytes(wstr);
}

}