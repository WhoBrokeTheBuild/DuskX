#include "FileUtil.hpp"

//#include <experimental/filesystem>

namespace dusk {

namespace util {

//namespace fs = std::experimental::filesystem;

wstring PathBasename(const wstring& path)
{
    return wstring();
    //return fs::path(path).filename().wstring();
}

wstring PathDirname(const wstring& path)
{
    return wstring();
    //return fs::path(path).root_directory().wstring();
}

wstring FileExtension(const wstring& path)
{
    return wstring();
    //return fs::path(path).extension().wstring();
}

wstring PathClean(wstring path)
{
    return wstring();
    //return fs::path(path).generic_wstring();
}

}

}