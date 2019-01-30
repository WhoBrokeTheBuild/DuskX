#ifndef DUSK_FILE_UTIL_HPP
#define DUSK_FILE_UTIL_HPP

#include <string>

namespace dusk {

using std::wstring;

/**
 * Returns the base filename of the given path.
 *
 * Example:
 *   Basename("/path/to/file.txt"); // file.txt
 *   Basename("C:\Path\To\file.txt"); // file.txt
 *
 * @param  path  A filepath
 *
 * @return The base filename of the path, or the path
 */
wstring PathBasename(const wstring& path);

/**
 * Returns the directory of the given path.
 * Always has a trailing path separator.
 *
 * Example:
 *   Basename("/path/to/file.txt"); // /path/to/
 *   Basename("C:\Path\To\file.txt"); // C:\Path\To\
 *
 * @param  path  A filepath
 *
 * @return The directory of the path, or "./"
 */
wstring PathDirname(const wstring& path);

/**
 * Returns the extension of the given path.
 *
 * Example:
 *   Basename("/path/to/file.txt"); // .txt
 *   Basename("/path/to/file.test.txt"); // .txt
 *   Basename("/path/to/file"); //
 *   Basename("/path/to/"); //
 *
 * @param  path  A filepath
 *
 * @return The extension of the path, or ""
 */
wstring FileExtension(const wstring& path);

/**
 * Returns the cleaned, simplified version of the given path.
 *
 * Example:
 *   Basename("./path/to/../to//file.txt"); // ./path/to/file.txt
 *   Basename("C:\Path/To\\..\To/file.txt"); // C:\Path\To\file.txt
 *
 * @param  path  A filepath
 *
 * @return The cleaned, simplified version of the path, or ""
 */
wstring PathClean(wstring path);

}

#endif // DUSK_FILE_UTIL_HPP
