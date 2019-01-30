#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <Util.hpp>

#include <string>

namespace dusk {

using std::string;
using std::wstring;

/**
 * Convert a string to a wide string
 * 
 * @param  str  A string
 * 
 * @return The converted wide string
 */
DUSKUTILAPI wchar_t * StringToWString(const char * str);

/**
 * Convert a std::wstring to a std::string
 * 
 * @param  str  A std::wstring
 * 
 * @return The converted std::string
 */
DUSKUTILAPI char * WStringToString(const wchar_t * wstr);

}

#endif // STRING_UTIL_HPP