#include "raygame/core/drawing/pixel.h" // IWYU pragma: keep
#include "raygame/core/test/tests_begin.h"

TEST_SUITE("core::Pixel") {
    TEST_CASE("String functions") {
        const auto        mod = core::colour::rgba(23, 12, 14, 16);
        const std::string mod_str{"Pixel(r: 23, g: 12, b: 14, a: 16)"};
        CHECK_EQ(std::string(mod), mod_str);
        CHECK_EQ(std::format("{}", mod), mod_str);
    }
}
