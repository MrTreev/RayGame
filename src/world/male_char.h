#pragma once
#include "core/actor.h"
#include "core/animatedspritesheet.h"
#include <string>

namespace world {

enum class MalePCActs {
    idle   = 0,
    walk   = 1,
    run    = 2,
    jump   = 3,
    fall   = 4,
    attack = 5,
    death  = 6,
};

inline std::string to_string(MalePCActs act) {
    switch (act) {
    case MalePCActs::idle:   return "Idle  ";
    case MalePCActs::walk:   return "Walk  ";
    case MalePCActs::run:    return "Run   ";
    case MalePCActs::jump:   return "Jump  ";
    case MalePCActs::fall:   return "Fall  ";
    case MalePCActs::attack: return "Attack";
    case MalePCActs::death:  return "Death ";
    }
}

class MalePC: public core::Actor<MalePCActs> {
private:
    core::AnimatedSpriteSheet<7> _spritesheet{
        "",
        {{5, 8, 8, 3, 3, 6, 10}},
        {{15, 15, 15, 15, 15, 15, 15}},
        10
    };
    static const int _fps = 15;

public:
    void draw();
};
} // namespace world
