#include "FileUtil.hpp"
#include <gtest/gtest.h>

using namespace dusk::util;

TEST(PathBasename, Empty)
{
    ASSERT_EQ(PathBasename(L""), L"");
}

TEST(PathBasename, Filename)
{
    ASSERT_EQ(PathBasename(L"file"), L"file");
    ASSERT_EQ(PathBasename(L"file.txt"), L"file.txt");
}

TEST(PathBasename, AbsolutePath)
{
    ASSERT_EQ(PathBasename(L"/file"), L"file");
    ASSERT_EQ(PathBasename(L"/."), L".");
    ASSERT_EQ(PathBasename(L"/path/to/file.txt"), L"file.txt");
    ASSERT_EQ(PathBasename(L"/path/with space/file.png"), L"file.png");

    ASSERT_EQ(PathBasename(L"C:\\file"), L"file");
    ASSERT_EQ(PathBasename(L"D:\\path\\to\\file.txt"), L"file.txt");
    ASSERT_EQ(PathBasename(L"E:\\path\\with space\\file.png"), L"file.png");
}

TEST(PathBasename, RelativePath)
{
    ASSERT_EQ(PathBasename(L"path/to/file"), L"file");
    ASSERT_EQ(PathBasename(L"path/to/."), L".");
    ASSERT_EQ(PathBasename(L"path/./file"), L"file");
    ASSERT_EQ(PathBasename(L"path/.."), L"..");
    ASSERT_EQ(PathBasename(L"./path/file"), L"file");
    ASSERT_EQ(PathBasename(L"path/to/../file"), L"file");
    ASSERT_EQ(PathBasename(L"path/with space/file"), L"file");
}

TEST(PathDirname, Empty)
{
    ASSERT_EQ(PathDirname(L""), L"./");
}

TEST(PathDirname, AbsolutePath)
{
    ASSERT_EQ(PathDirname(L"/path/to/file"), L"/path/to/");
    ASSERT_EQ(PathDirname(L"/path/with space/file"), L"/path/with space/");

    ASSERT_EQ(PathDirname(L"C:\\path\\to\\file"), L"C:\\path\\to\\");
    ASSERT_EQ(PathDirname(L"C:\\path\\with space\\file"), L"C:\\path\\with space\\");
}

TEST(PathDirname, RelativePath)
{
    ASSERT_EQ(PathDirname(L"path/to/file"), L"path/to/");
    ASSERT_EQ(PathDirname(L"path/with space/file"), L"path/with space/");
}

TEST(FileExtension, Empty)
{
    ASSERT_EQ(FileExtension(L""), L"");
}

TEST(FileExtension, NoExtension)
{
    ASSERT_EQ(FileExtension(L""), L"");
    ASSERT_EQ(FileExtension(L"FileWithNoExt"), L"");
    ASSERT_EQ(FileExtension(L"/path/to/file"), L"");
}

TEST(FileExtension, AbsolutePath)
{
    ASSERT_EQ(FileExtension(L"/path/to/file.txt"), L"txt");
    ASSERT_EQ(FileExtension(L"/path/with space/file.JPEG"), L"JPEG");

    ASSERT_EQ(FileExtension(L"C:\\path\\to\\file"), L"C:\\path\\to\\");
    ASSERT_EQ(FileExtension(L"C:\\path\\with space\\file"), L"C:\\path\\with space\\");
}

TEST(PathClean, Empty)
{
    ASSERT_EQ(PathClean(L""), L"");
}

TEST(PathClean, AbsolutePath)
{
    ASSERT_EQ(PathClean(L"path/to/file"), L"path/to/file");
    ASSERT_EQ(PathClean(L"path/../to/file"), L"to/file");
    ASSERT_EQ(PathClean(L"path/to/./file"), L"path/to/file");
}

TEST(PathClean, RelativePath)
{
    ASSERT_EQ(PathClean(L"path/to/file"), L"path/to/file");
    ASSERT_EQ(PathClean(L"path/../to/file"), L"to/file");
    ASSERT_EQ(PathClean(L"path/to/./file"), L"path/to/file");
}

int main(int argc, char **argv) 
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}