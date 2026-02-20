#include "raygame/core/io/file.h"
#include "raytest/raytest.h"
#include <filesystem>
#include <sys/wait.h>
#include <unistd.h>

#if !defined(TEST_DATA_DIR)
#    define TEST_DATA_DIR "TEST_DATA_DIR"
#endif

#if !defined(TEST_FILE_DIR)
#    define TEST_FILE_DIR "TEST_FILE_DIR"
#endif

RT_TEST(File, stuff) {
    const std::filesystem::path paths_data{TEST_DATA_DIR};
    // const std::filesystem::path paths_file{TEST_FILE_DIR};
    RT_SUBCASE("slurpfile") {
        const std::filesystem::path slurpfile{paths_data / "slurpfile"};
        const std::string           slurpfile_desired =
            "test first line\n"
            "second line\n"
            "more simple stuff\n";
        const core::io::File slurpfile_file{slurpfile, "r"};
        const std::string    slurpfile_actual{slurpfile_file.slurp()};
        RT_CHECK_EQ(slurpfile_desired, slurpfile_actual);
    }
}
