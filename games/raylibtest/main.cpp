#include "raygame/core/window/window.h"
#include "test.h"

constexpr core::Vec2<size_t> WIN_SIZE = {1280, 720};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    using core::Pixel;
    using core::drawing::ImageView;
    auto image = test::imgtest;

    core::window::Window mywindow{WIN_SIZE};

    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
