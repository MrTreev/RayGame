#include "games/image/defs.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/window/window.h"
constexpr core::Vec2<size_t> IMG_SIZE = {400, 400};
constexpr core::Vec2<size_t> WIN_SIZE = {640, 640};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    core::window::Window     mywindow{WIN_SIZE};
    core::drawing::ImageView image{resources::img_icon, IMG_SIZE};
    image.move(400, 400);
    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
