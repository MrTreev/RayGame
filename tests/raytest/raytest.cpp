#include "raytest.h" // IWYU pragma: keep
#include "raygame/core/config.h"
#include <filesystem>
#include <print>
#include <rules_cc/cc/runfiles/runfiles.h>
#include <source_location>

namespace {
using rules_cc::cc::runfiles::Runfiles;

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RAYGAME_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
//NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::unique_ptr<Runfiles> runfile{nullptr};
RAYGAME_CLANG_SUPPRESS_WARNING_POP
} // namespace

namespace test {

std::filesystem::path datafile(const std::string& data_name) {
    //NOLINTNEXTLINE(*-redundant-string-init)
    std::string root{BAZEL_CURRENT_REPOSITORY};
    if (root.empty()) {
        root = "_main";
    }
    std::filesystem::path file{runfile->Rlocation(std::filesystem::path(root) / data_name)};
    return file;
}

std::filesystem::path newfile(const std::string& file_name) {
    //NOLINTNEXTLINE(concurrency-mt-unsafe)
    const auto* test_tmpdir = std::getenv("TEST_TMPDIR");
    if (test_tmpdir == nullptr) {
        return {"./" + file_name};
    }
    return {std::filesystem::path(test_tmpdir) / file_name};
}

} // namespace test

int main(int argc, char** argv) {
    int retval{1};
    try {
        const auto loc = std::source_location::current();
        std::println("Running main() from {}", loc.file_name());
        runfile.reset(Runfiles::CreateForTest());
        testing::InitGoogleTest(&argc, argv);
        retval = RUN_ALL_TESTS();
    } catch (...) { // NOLINT(bugprone-empty-catch)
    }
    return retval;
}
