#include "raytest/raytest.h"
#include <sys/wait.h>
#include <unistd.h>

#ifndef RESMK
#    define RESMK "RESMK"
#endif
#ifndef RESMK_DATA_DIR
#    define RESMK_DATA_DIR "RESMK_DATA_DIR"
#endif
#ifndef RESMK_FILE_DIR
#    define RESMK_FILE_DIR "RESMK_FILE_DIR"
#endif

namespace {
using cstr = const char* const;
constexpr std::string exe{RESMK};
constexpr std::string datadir{RESMK_DATA_DIR};
constexpr std::string filedir{RESMK_FILE_DIR};

int resmk(cstr hdr, cstr png) {
    int       status = 0;
    const int pid    = fork();
    if (pid != 0) {
        waitpid(pid, &status, 0);
    } else {
        const char* const executable{exe.c_str()};
        // NOLINTNEXTLINE(*-vararg)
        execl(executable, executable, hdr, png, nullptr);
    }
    return status;
}

} // namespace

RG_TEST(ResMK, stuff) {
    RG_SUBCASE("imgtest") {
        constexpr std::string imgtest_hdr = filedir + "/imgtest.h";
        constexpr std::string imgtest_src = filedir + "/imgtest.cpp";
        constexpr std::string imgtest_png = datadir + "/imgtest.png";
        RG_CHECK_EQ(0, resmk(imgtest_hdr.c_str(), imgtest_png.c_str()));
    }
}
