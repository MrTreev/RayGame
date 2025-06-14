#include "raytest.h"
#include <print>
#include <source_location>

int main(int argc, char** argv) {
    const auto loc = std::source_location::current();
    std::println("Running main() from {}", loc.file_name());
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
