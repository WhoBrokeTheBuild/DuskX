#ifndef DUSK_DESKTOP_HPP
#define DUSK_DESKTOP_HPP

#if _WIN32
#   ifdef DuskDesktop_EXPORT
#       define DUSKDESKTOPAPI __declspec(dllexport)
#   else
#       define DUSKDESKTOPAPI __declspec(dllimport)
#   endif // DuskDesktop_EXPORT
#else
#   define DUSKDESKTOPAPI
#endif // _WIN32

#endif // DUSK_DESKTOP_HPP