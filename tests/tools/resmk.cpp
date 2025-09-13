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

int resmk(cstr hdr, cstr png) {
    int       status = 0;
    const int pid    = fork();
    if (pid != 0) {
        waitpid(pid, &status, 0);
    } else {
        const char* const executable{RESMK};
        // NOLINTNEXTLINE(*-vararg)
        execl(executable, executable, hdr, png, nullptr);
    }
    return status;
}

// cstr imgtest_header{};
// cstr imgtest_source{};

} // namespace

RG_TEST(ResMK, stuff) {
    RG_SUBCASE("imgtest") {
        cstr imgtest_hdr{RESMK_FILE_DIR "/imgtest.h"};
        cstr imgtest_png{RESMK_DATA_DIR "/imgtest.png"};
        RG_CHECK_EQ(0, resmk(imgtest_hdr, imgtest_png));
        [[maybe_unused]]
        cstr imgtest_src{RESMK_FILE_DIR "/imgtest.cpp"};
    }
}
