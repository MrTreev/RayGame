#pragma once
#include "lib/spritesheet.h"
#include "objects/actor.h"

enum TopdownActs {
    Down  = 0,
    Left  = 1,
    Right = 2,
    Up    = 3
};

class TopdownChar: public Actor<TopdownActs> {
public:
    void move(raylib::Vector2 delta) {
        Actor::move(delta);
        move_action(delta.x, delta.y);
    }

    void move(float delta_x, float delta_y) {
        Actor::move(delta_x, delta_y);
        move_action(delta_x, delta_y);
    }

    void draw() {
        _spritesheet.draw(position(), action());
    }

private:
    void move_action(float delta_x, float delta_y) {
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
    };

    lib::SpriteSheet<4> _spritesheet{
        "resources/raw/Free RGW Sprites/Free RGW Sprites/48x48",
        {4, 4, 4, 4},
        {8, 8, 8, 8},
        4
    };
};
