#include "games/image/defs.h"
#include "raygame/core/application/application.h"
#include "raygame/core/drawing/image.h"

constexpr core::Vec2<core::dis_t> IMG_SIZE = {400, 400};
constexpr core::Vec2<core::pos_t> IMG_POS  = {100, 100};

// NOLINTNEXTLINE(*-exception-escape)
int main() {
    core::Application              myapp;
    const core::drawing::ImageView m_image{resources::img_icon, IMG_SIZE};
    while (myapp.next_frame()) {
        myapp.draw(m_image, IMG_POS);
    }
}
