#include "raygame/core/io/file.h"
#include "raytest/raytest.h"
#include <filesystem>
#include <sys/wait.h>
#include <unistd.h>

RT_TEST(File, stuff) {
    RT_SUBCASE("slurpfile") {
        const std::filesystem::path slurpfile{test::datafile("tests/core/io/data/slurpfile")};
        std::println("slurpfile: {}", slurpfile.string());
        RT_ASSERT(std::filesystem::exists(slurpfile));

        const std::string           slurpfile_desired{
            "test first line\n"
            "second line\n"
            "more simple stuff\n"
        };
        const core::io::File slurpfile_file{slurpfile, "r"};
        const std::string    slurpfile_actual{slurpfile_file.slurp()};
        RT_CHECK_EQ(slurpfile_desired, slurpfile_actual);
    }
}
