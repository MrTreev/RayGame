#include "games/image/defs.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/window/window.h"
constexpr core::Vec2<size_t> IMG_SIZE = {400, 400};

int main() {
    core::window::Window       mywindow{{1280, 720}};
    const core::drawing::Image image{resources::icon_argb8888, IMG_SIZE};
    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
