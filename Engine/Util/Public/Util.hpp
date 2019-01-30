#ifndef DUSK_UTIL_HPP
#define DUSK_UTIL_HPP

#if _WIN32
#   ifdef DuskUtil_EXPORT
#       define DUSKUTILAPI __declspec(dllexport)
#   else
#       define DUSKUTILAPI __declspec(dllimport)
#   endif // DuskUtil_EXPORT
#else
#   define DUSKUTILAPI
#endif // _WIN32

#endif // DUSK_UTIL_HPP