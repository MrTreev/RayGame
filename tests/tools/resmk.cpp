#include "raytest/raytest.h"
#include <sys/wait.h>
#include <unistd.h>

namespace {
#if defined(RESMK)
constexpr std::string resmk_name = RESMK;
#else
constexpr std::string resmk_name = "RESMK";
#endif

#if defined(RESMK_DATA_DIR)
constexpr std::string resmk_data_dir = RESMK_DATA_DIR;
#else
constexpr std::string resmk_data_dir = "RESMK_DATA_DIR";
#endif

#if defined(RESMK_FILE_DIR)
constexpr std::string resmk_data_dir = RESMK_FILE_DIR;
#else
constexpr std::string resmk_file_dir = "RESMK_FILE_DIR";
#endif
using cstr = const char* const;

int resmk(const std::string& hdr, const std::string& png) {
    int       status = 0;
    const int pid    = fork();
    if (pid != 0) {
        waitpid(pid, &status, 0);
    } else {
        // NOLINTNEXTLINE(*-vararg)
        execl(resmk_name.c_str(), resmk_name.c_str(), hdr.c_str(), png.c_str(), nullptr);
    }
    return status;
}
} // namespace

RG_TEST(ResMK, stuff) {
    RG_SUBCASE("imgtest") {
        const std::string imgtest_hdr{resmk_file_dir + "/imgtest.h"};
        const std::string imgtest_png{resmk_data_dir + "/imgtest.png"};
        RG_CHECK_EQ(0, resmk(imgtest_hdr, imgtest_png));
        [[maybe_unused]]
        const std::string imgtest_src{resmk_file_dir + "/imgtest.cpp"};
    }
}
