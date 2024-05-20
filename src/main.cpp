#include "config.h"
#include "world/topdown_char.h"
#include "core/raycpp/input.h"
#include "core/raycpp/keyboard.h"
#include "core/raycpp/window.h"

int main() {
	core::raycpp::Window window(config::game_name.data());
    core::raycpp::Window::SetTargetFPS(config::frame_rate);
    constexpr int tile_size = 48;
	world::TopdownChar   player;
    while (!core::raycpp::Window::ShouldClose()) {
		core::raycpp::Window::BeginDrawing();
        core::raycpp::Window::ClearBackground();
        while (const auto key = core::raycpp::Keyboard::GetKeyPressed()) {
            using core::raycpp::Key;
            switch (key) {
            // case Key::SPACE: player.toggle_state();
            case Key::W: player.move({0, -tile_size}); break;
            case Key::A: player.move({-tile_size, 0}); break;
            case Key::S: player.move({0, tile_size}); break;
            case Key::D: player.move({tile_size, 0}); break;
            default:     break;
            }
        }
        player.draw();
		core::raycpp::Window::DrawFPS();
		core::raycpp::Window::EndDrawing();
    }
    return 0;
}
