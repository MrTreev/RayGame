#include "raygame/core/drawing/pixel.hpp" // IWYU pragma: keep
#include "raytest/raytest.hpp"

RT_TEST(Pixel, StringFunctions) {
    const auto        mod = core::colour::rgba(23, 12, 14, 16);
    const std::string mod_str{"Pixel(r: 23, g: 12, b: 14, a: 16)"};
    RT_CHECK_EQ(std::string(mod), mod_str);
    RT_CHECK_EQ(std::format("{}", mod), mod_str);
}
