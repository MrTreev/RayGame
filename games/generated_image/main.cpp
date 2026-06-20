#include "games/generated_image/generated_png_image.h"
#include "raygame/core/application/application.h"

int main() {
    core::Application mywindow{};
    using generated_png_image::pngtest;
    using generated_png_image::square;
    constexpr size_t sq_x{100};
    constexpr size_t sq_y{100};
    while (mywindow.next_frame()) {
        mywindow.draw(pngtest, {0, 0});
        mywindow.draw(square, {sq_x, sq_y});
    }
}
