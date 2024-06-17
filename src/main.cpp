#include "core/gui/window.h"
#include "core/image.h"
#include "core/texture.h"
#include "core/types.h"
#include <string_view>

int main() {
    std::string_view  filename = "resources/Weapon-Asset-Part1.png";
    core::gui::Window game_window;
    game_window.set_framerate(15);
    core::Texture       texidle(filename);
    core::Vec2<int32_t> pos(10, 10);
    game_window.draw_fps(true);
    while (!game_window.should_close()) {
        game_window.clear();
        texidle.draw(pos);
        game_window.display();
    }
}
