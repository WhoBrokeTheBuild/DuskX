#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <regex>
#include <array>
#include <atomic>
#include <thread>

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
#if defined(_WIN32)
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "rt"), _pclose);
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

    std::atomic_bool noTabs = true;
    std::atomic_bool noCarriageReturns = true;
    std::atomic_bool noTrailingSpace = true;

    std::vector<std::thread> threads;

    auto checkFile = [&noTabs, &noCarriageReturns, &noTrailingSpace](std::string filename)
    {
        size_t pivot = filename.find_last_of('.');
        std::string ext = filename.substr(pivot);

        if (ext != ".h" && ext != ".hpp"
            && ext != ".c" && ext != ".cpp"
            && ext != ".txt" && ext != ".cmake") {
            return;
        }

        std::regex reFindTabs(R"((\t))");
        std::regex reFindTrailingSpace(R"(([ \t]+(?=\n|$)))");
#if !defined(_WIN32)
        std::regex reFindCarriageReturn(R"((\r))");
#endif

        std::ifstream file(filename, std::ifstream::binary | std::ifstream::ate);
        if (!file) {
            return;
        }

        size_t size = file.tellg();
        file.seekg(0);

        std::vector<char> buffer(size + 1);
        file.read(&buffer[0], buffer.size());
        buffer.back() = '\0';

        std::cmatch cm;
        std::regex_search(buffer.data(), cm, reFindTabs);
        if (!cm.empty()) {
            printf("File has tabs '%s'\n", filename.c_str());
            noTabs = false;
        }

#if !defined(_WIN32)
        std::regex_search(buffer.data(), cm, reFindCarriageReturn);
        if (!cm.empty()) {
            printf("File has carriage returns '%s'\n", filename.c_str());
            noCarriageReturns = false;
        }
#endif

        std::regex_search(buffer.data(), cm, reFindTrailingSpace, std::regex_constants::match_not_eol);
        if (!cm.empty()) {
            printf("File has trailing whitespace '%s'\n", filename.c_str());
            noTrailingSpace = false;
        }
    };

    std::vector<std::string> files;
    std::stringstream ss(fileList);
    for (std::string filename; std::getline(ss, filename); ) {
        files.push_back(filename);
    }

    for (const auto& file : files) {
        threads.push_back(std::thread(checkFile, std::string(file)));
    }

    for (auto& t : threads) {
        t.join();
    }

    if (noTabs && noCarriageReturns && noTrailingSpace) {
        return 0;
    }

    return 1;
}
