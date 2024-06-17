#include "core/gui/window.h"
#include "core/image.h"
#include "core/texture.h"
#include "core/types.h"
#include <raylib.h>
#include <string_view>

int main() {
    std::string_view  filename = "resources/Weapon-Asset-Part1.png";
    core::gui::Window game_window;
    game_window.set_framerate(15);
    core::Image         idle(filename);
    core::Texture       texidle(idle);
    core::Vec2<int32_t> pos(10, 10);
    game_window.draw_fps(true);
    ::Texture img = ::LoadTexture(filename.data());
    while (!game_window.should_close()) {
        game_window.clear();
        ::DrawTexture(img, 10, 10, WHITE);
        texidle.draw(pos);
        game_window.display();
    }
}
