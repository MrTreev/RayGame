#include "objects/topdown_char.h"

void TopdownChar::move_action(float delta_x, float delta_y) {
    if (std::abs(delta_x) > std::abs(delta_y)) {
        if (delta_x > 0) {
            action(TopdownActs::Right);
        } else if (delta_x < 0) {
            action(TopdownActs::Left);
        }
    } else if (std::abs(delta_x) <= std::abs(delta_y)) {
        if (delta_y < 0) {
            action(TopdownActs::Up);
        } else {
            action(TopdownActs::Down);
        }
    }
}

void TopdownChar::move(raylib::Vector2 delta) {
    Actor::move(delta);
    move_action(delta.x, delta.y);
}

void TopdownChar::move(float delta_x, float delta_y) {
    Actor::move(delta_x, delta_y);
    move_action(delta_x, delta_y);
}

void TopdownChar::draw() {
    _spritesheet.draw(position(), std::size_t(action()), 1);
}
