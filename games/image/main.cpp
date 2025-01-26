#include "games/image/defs.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/window/window.h"
constexpr core::Vec2<size_t> IMG_SIZE = {92, 96};
constexpr core::Vec2<size_t> WIN_SIZE = {400, 400};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    core::window::Window mywindow{WIN_SIZE};
    core::drawing::Image image{resources::img_argb8888, IMG_SIZE};
    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
