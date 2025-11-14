#include "raytest.h"
#include <print>
#include <source_location>

int main(int argc, char** argv) {
    try {
        const auto loc = std::source_location::current();
        std::println("Running main() from {}", loc.file_name());
        testing::InitGoogleTest(&argc, argv);
    } catch (...) { // NOLINT(bugprone-empty-catch)
    }
    return RUN_ALL_TESTS();
}
