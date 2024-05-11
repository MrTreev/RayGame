#pragma once
#include "lib/spritesheet.h"
#include "objects/actor.h"

enum class TopdownActs {
    Down  = 0,
    Left  = 1,
    Right = 2,
    Back  = 3
};

class TopdownChar: public Actor<TopdownActs> {
private:
    lib::SpriteSheet<4> _spritesheet{
        "resources/raw/Free RGW Sprites/Free RGW Sprites/48x48",
        {4, 4, 4, 4},
        {8, 8, 8, 8},
        4
    };
};
