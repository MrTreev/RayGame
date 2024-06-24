#include "core/logger.h"
#include "core/window.h"
#include <string_view>

int main() {
    std::string_view filename = "etc/images/Weapon-Asset-Part1.png";
    core::Window     game_window;
    while (!game_window.should_close()) {
        core::log::debug("Tick");
    }
}
