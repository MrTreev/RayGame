#include "generated/generated_png_image.h"
#include "raygame/core/application/application.h"

int main() {
    core::Application mywindow{};
    while (mywindow.next_frame()) {
        mywindow.draw(generated_png_image::pngtest);
    }
}
