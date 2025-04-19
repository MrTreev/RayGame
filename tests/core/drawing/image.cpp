#include "raygame/core/drawing/image.h"
#include "raygame/core/drawing/pixel.h"
#include "raytest/tests_begin.h"

TEST_SUITE("core::drawing::image") {
    TEST_CASE("Construct Image") {
        const std::array<core::Pixel, 9> arr9_test{
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0),
            core::colour::rgb(0, 0, 0)
        };
        const core::drawing::ImageView img9_test{
            arr9_test,
            {3UL, 3UL}
        };
    }
}
