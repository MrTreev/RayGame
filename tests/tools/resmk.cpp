#include "raygame/tools/resmk/resources/resmk.hpp"
#include "raygame/core/io/file.hpp"
#include "raytest/raytest.hpp"
#include <filesystem>
#include <unistd.h>

namespace {
int runprog(const std::string& hdr, const std::string& png) {
    const std::filesystem::path resmk_name = test::datafile("raygame/tools/resmk/resmk");
    int                         status     = 0;
    const int                   pid        = fork();
    if (pid != 0) {
        waitpid(pid, &status, 0);
    } else {
        // NOLINTNEXTLINE(*-vararg)
        execl(resmk_name.c_str(), resmk_name.c_str(), hdr.c_str(), png.c_str(), nullptr);
    }
    return status;
}
} // namespace

RT_TEST(ResMK, stuff) {
    const std::filesystem::path resmk_data{test::datafile("tests/tools/data")};
    const std::filesystem::path pngtest_png{resmk_data / "pngtest.png"};
    const std::filesystem::path desired_src{resmk_data / "pngtest.cpp"};
    const std::filesystem::path desired_hdr{resmk_data / "pngtest.hpp"};

    RT_SUBCASE("Full program test") {
        const std::string           base{"pngtest"};
        const std::filesystem::path pngtest_hdr{test::newfile(std::format("{}.hpp", base))};
        const std::filesystem::path pngtest_src{test::newfile(std::format("{}.cpp", base))};

        RT_CHECK_EQ(0, runprog(pngtest_hdr, pngtest_png));
        RT_ASSERT(std::filesystem::exists(pngtest_png));

        RT_CHECK_TRUE(std::filesystem::exists(pngtest_hdr));
        const std::string hdrfile_content{core::io::File(pngtest_hdr, "r").slurp()};
        const std::string hdrfile_desired{core::io::File(desired_hdr, "r").slurp()};
        RT_CHECK_EQ(hdrfile_content, hdrfile_desired);

        RT_CHECK_TRUE(std::filesystem::exists(pngtest_src));
        const std::string srcfile_content{core::io::File(pngtest_src, "r").slurp()};
        const std::string srcfile_desired{core::io::File(desired_src, "r").slurp()};
        RT_CHECK_EQ(srcfile_content, srcfile_desired);
        std::filesystem::remove(pngtest_hdr);
        std::filesystem::remove(pngtest_src);
    }
    RT_SUBCASE("Library test") {
        const std::string           base{"pngtest"};
        const std::filesystem::path pngtest_hdr{test::newfile(std::format("{}.hpp", base))};
        const std::filesystem::path pngtest_src{test::newfile(std::format("{}.cpp", base))};

        const std::vector<std::filesystem::path> paths{pngtest_png};
        resmk::resmk(pngtest_hdr, paths, base, base);
        RT_ASSERT(std::filesystem::exists(pngtest_png));

        RT_CHECK_TRUE(std::filesystem::exists(pngtest_hdr));
        const std::string hdrfile_content{core::io::File(pngtest_hdr, "r").slurp()};
        const std::string hdrfile_desired{core::io::File(desired_hdr, "r").slurp()};
        RT_CHECK_EQ(hdrfile_content, hdrfile_desired);

        RT_CHECK_TRUE(std::filesystem::exists(pngtest_src));
        const std::string srcfile_content{core::io::File(pngtest_src, "r").slurp()};
        const std::string srcfile_desired{core::io::File(desired_src, "r").slurp()};
        RT_CHECK_EQ(srcfile_content, srcfile_desired);
        std::filesystem::remove(pngtest_hdr);
        std::filesystem::remove(pngtest_src);
    }
}
