#include "config.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::Window window(
        sf::VideoMode(640, 480, 32),
        config::game_name.data(),
        sf::Style::Fullscreen
    );
    return 0;
}
