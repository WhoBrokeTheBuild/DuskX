#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <regex>
#include <array>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
#if defined(_WIN32)
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
#endif
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char** argv)
{
    auto fileList = exec("git ls-tree -r master --name-only");
    std::regex reFindTabs(R"((\t))");
    std::regex reFindCarriageReturn(R"((\r))");
    std::regex reFindTrailingSpace(R"(([ \t]+(?=\n|$)))");

    bool noTabs = true;
    bool noCarriageReturns = true;
    bool noTrailingSpace = true;
    std::stringstream ss(fileList);
    for (std::string filename; std::getline(ss, filename); ) {
        if (fs::path(filename).filename() == "Makefile") {
            continue;
        }

        std::error_code ec;
        uintmax_t size = fs::file_size(filename, ec);
        if (!ec) {
            std::ifstream file(filename);
            std::string data(size, '\0');
            file.read(&data[0], size);

            std::smatch sm;
            std::regex_search(data, sm, reFindTabs);
            if (!sm.empty()) {
                fprintf(stderr, "File has tabs '%s'\n", filename.c_str());
                noTabs = false;
            }

            std::regex_search(data, sm, reFindCarriageReturn);
            if (!sm.empty()) {
                fprintf(stderr, "File has carriage returns '%s'\n", filename.c_str());
                noCarriageReturns = false;
            }

            std::regex_search(data, sm, reFindTrailingSpace, std::regex_constants::match_not_eol);
            if (!sm.empty()) {
                fprintf(stderr, "File has trailing whitespace '%s'\n", filename.c_str());
                noTrailingSpace = false;
            }
        }
    }

    if (noTabs && noCarriageReturns && noTrailingSpace) {
        return 0;
    }

    return 1;
}
