#include "raygame/core/drawing/image.h"
#include "raygame/core/drawing/pixel.h"
#include "raytest/raytest.h"

RT_TEST(Image, Constructors) {
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
