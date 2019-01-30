#ifndef DUSK_CORE_HPP
#define DUSK_CORE_HPP

#if _WIN32
#   ifdef DuskCore_EXPORT
#       define DUSKCOREAPI __declspec(dllexport)
#   else
#       define DUSKCOREAPI __declspec(dllimport)
#   endif // DuskCore_EXPORT
#else 
#   define DUSKCOREAPI
#endif // _WIN32

#endif // DUSK_CORE_HPP