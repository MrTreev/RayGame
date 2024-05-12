#pragma once
#include "lib/spritesheet.h"
#include "objects/actor.h"

enum TopdownActs {
    Down  = 0,
    Left  = 1,
    Right = 2,
    Up    = 3,
};

class TopdownChar: public Actor<TopdownActs> {
private:
    void move_action(float delta_x, float delta_y);

    lib::SpriteSheet<4> _spritesheet{
        "resources/raw/Free RGW Sprites/Free RGW Sprites/48x48",
        {4, 4, 4, 4},
        {8, 8, 8, 8},
        4
    };

public:
    void draw();
    void move(raylib::Vector2 delta);
    void move(float delta_x, float delta_y);
};
