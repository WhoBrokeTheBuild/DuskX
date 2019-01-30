#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

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
wstring StringToWString(const string& str);

/**
 * Convert a std::wstring to a std::string
 *
 * @param  str  A std::wstring
 *
 * @return The converted std::string
 */
string WStringToString(const wstring& wstr);

}

#endif // STRING_UTIL_HPP
