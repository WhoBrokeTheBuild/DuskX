#include "FileUtil.hpp"

#include <experimental/filesystem>

namespace dusk {

namespace fs = std::experimental::filesystem;

wstring PathBasename(const wstring& path)
{
    if (path.empty()) {
        return wstring();
    }
    return fs::path(path).filename().wstring();
}

wstring PathDirname(const wstring& path)
{
    if (path.empty()) {
        return L"./";
    }
    return fs::path(path).parent_path().wstring() + L"/";
}

wstring FileExtension(const wstring& path)
{
    if (path.empty()) {
        return wstring();
    }
    return fs::path(path).extension().wstring();
}

wstring PathClean(wstring path)
{
    if (path.empty()) {
        return wstring();
    }
    return fs::canonical(fs::path(path)).wstring();
}

}