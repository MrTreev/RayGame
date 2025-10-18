#include "games/image/defs.h"
#include "raygame/core/application.h"
#include "raygame/core/window/window.h"

constexpr core::Vec2<size_t> IMG_SIZE = {400, 400};
constexpr core::Vec2<size_t> IMG_POS  = {100, 100};
constexpr core::Vec2<size_t> WIN_SIZE = {1280, 720};

class MyApp: core::Application {
    void main() {
        while (m_window.next_frame()) {
            m_window.draw(image);
        }
    }
};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    core::Application        myapp{WIN_SIZE};
    core::drawing::ImageView image{resources::img_icon, IMG_SIZE};
    image.move(IMG_POS.x, IMG_POS.y);
}
