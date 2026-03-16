#include "generated/generated_png_image.h"
#include "raygame/core/application/application.h"

int main() {
    core::Application mywindow{};
    generated_png_image::square.move(100, 100);
    while (mywindow.next_frame()) {
        mywindow.draw(generated_png_image::pngtest, {0, 0});
        mywindow.draw(generated_png_image::square, {100, 100});
    }
}
