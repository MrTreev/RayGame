#include "config.h"
#include "core/logger.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(
        sf::VideoMode(
            config::default_window_width,
            config::default_window_width
        ),
        config::game_name.data(),
        sf::Style::Fullscreen
    );
    window.setFramerateLimit(config::frame_rate);

    sf::CircleShape shape(100.F);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event{};
        core::log::trace("Frame");
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
