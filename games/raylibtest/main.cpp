#include "raygame/core/window/detail/wayland.h"
#include "raygame/core/window/window.h"
#include "test.h"

constexpr core::Vec2<size_t> WIN_SIZE = {1280, 720};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    using core::Pixel;
    using core::drawing::ImageView;
    auto image = test::imgtest;
    image.pos(0, 0);

    core::window::detail::WaylandWindowImpl mywindow{
        WIN_SIZE,
        "RayGame",
        core::window::WindowStyle::Windowed
    };
    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
