#include "games/image/defs.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/application.h"

constexpr core::Vec2<size_t> IMG_SIZE = {400, 400};
constexpr core::Vec2<size_t> IMG_POS  = {100, 100};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    core::Application myapp;
    core::drawing::ImageView  m_image{resources::img_icon, IMG_SIZE};
    m_image.move(IMG_POS.x, IMG_POS.y);
    while (myapp.next_frame()) {
        myapp.draw(m_image);
    }
}
