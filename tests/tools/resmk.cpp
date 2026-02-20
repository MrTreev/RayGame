#include "raygame/core/io/file.h"
#include "raytest/raytest.h"
#include <filesystem>
#include <sys/wait.h>
#include <unistd.h>

#if !defined(RESMK)
#    define RESMK "RESMK"
#endif

#if !defined(RESMK_DATA_DIR)
#    define RESMK_DATA_DIR "RESMK_DATA_DIR"
#endif

#if !defined(RESMK_FILE_DIR)
#    define RESMK_FILE_DIR "RESMK_FILE_DIR"
#endif

namespace {
int resmk(const std::string& hdr, const std::string& png) {
    const std::filesystem::path resmk_name = RESMK;
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
    const std::filesystem::path resmk_data = RESMK_DATA_DIR;
    const std::filesystem::path resmk_file = RESMK_FILE_DIR;

    RT_SUBCASE("png data") {
        std::filesystem::create_directory(resmk_file);
        const std::filesystem::path pngtest_png{resmk_data / "pngtest.png"};
        const std::filesystem::path pngtest_hdr{resmk_file / "pngtest.h"};
        RT_CHECK_EQ(0, resmk(pngtest_hdr, pngtest_png));
        RT_ASSERT(std::filesystem::exists(pngtest_png));

        RT_CHECK_TRUE(std::filesystem::exists(pngtest_hdr));
        const core::io::File pngtest_hdrfile{pngtest_hdr, "r"};
        const auto           hdrfile_content{pngtest_hdrfile.slurp()};

        const core::io::File desired_hdrfile{pngtest_hdr, "r"};
        const auto           hdrfile_desired{desired_hdrfile.slurp()};
        RT_CHECK_EQ(hdrfile_content, hdrfile_desired);

        const std::filesystem::path pngtest_src{resmk_file / "pngtest.cpp"};
        RT_CHECK_TRUE(std::filesystem::exists(pngtest_src));
        const core::io::File pngtest_srcfile{pngtest_src, "r"};
        const auto           srcfile_content{pngtest_srcfile.slurp()};
        const core::io::File desired_srcfile{pngtest_src, "r"};
        const auto           srcfile_desired{desired_srcfile.slurp()};
        RT_CHECK_EQ(srcfile_content, srcfile_desired);
    }
}
