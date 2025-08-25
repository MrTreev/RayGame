#include "games/image/defs.h"
#include "raygame/core/window/window.h"
#include "third_party/raylib/src/raylib.h"
#include <array>

constexpr core::Vec2<size_t> IMG_SIZE = {325, 325};
constexpr core::Vec2<size_t> IMG_POS  = {100, 100};
constexpr core::Vec2<size_t> WIN_SIZE = {1280, 720};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    using core::Pixel;
    using core::drawing::ImageView;
    using arr_t = std::array<core::Pixel, IMG_SIZE.x * IMG_SIZE.y>;

    core::window::Window mywindow{WIN_SIZE};

    ChangeDirectory(GetApplicationDirectory());
    const Image rayimg{LoadImage("BabySeal.png")};
    arr_t       test{};
    std::memcpy(test.data(), rayimg.data, IMG_SIZE.x * IMG_SIZE.y * sizeof(Pixel));
    ImageView image{test, IMG_SIZE};
    image.move(IMG_POS.x, IMG_POS.y);
    while (mywindow.next_frame()) {
        mywindow.draw(image);
    }
}
