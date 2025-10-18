#include "games/image/defs.h"
#include "raygame/core/application.h"

constexpr core::Vec2<size_t> IMG_SIZE = {400, 400};
constexpr core::Vec2<size_t> IMG_POS  = {100, 100};

class MyApp: core::Application {
    core::drawing::ImageView m_image{resources::img_icon, IMG_SIZE};

public:
    void main() {
        m_image.move(IMG_POS.x, IMG_POS.y);
        while (next_frame()) {
            draw(m_image);
        }
    }
};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    MyApp myapp;
    myapp.main();
}
