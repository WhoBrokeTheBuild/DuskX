#include "FileUtil.hpp"
#include <gtest/gtest.h>

#include <experimental/filesystem>

int main(int argc, char **argv) 
{
    printf("%ls\n", std::experimental::filesystem::path(L"/path/to").wstring().c_str());
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}