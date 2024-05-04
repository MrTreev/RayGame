#pragma once
#include "lib/animatedsprite.h"
#include "objects/actor.h"
#include <string>

enum class MalePCActs {
    idle,
    walk,
    run,
    jump,
    fall,
    attack,
    death,
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
};

class MalePC: public Actor<MalePCActs> {
private:
    static const int _fps           = 15;
    static const int _idle_frames   = 00;
    static const int _walk_frames   = 00;
    static const int _run_frames    = 00;
    static const int _jump_frames   = 00;
    static const int _fall_frames   = 00;
    static const int _attack_frames = 00;
    static const int _death_frames  = 00;

    lib::AnimatedSprite _idle{
        "resources/GandalfHardcore/PC/idle.png",
        _idle_frames,
        _fps
    };
    lib::AnimatedSprite _walk{
        "resources/GandalfHardcore/PC/walk.png",
        _walk_frames,
        _fps
    };
    lib::AnimatedSprite _run{
        "resources/GandalfHardcore/PC/run.png",
        _run_frames,
        _fps
    };
    lib::AnimatedSprite _jump{
        "resources/GandalfHardcore/PC/jump.png",
        _jump_frames,
        _fps
    };
    lib::AnimatedSprite _fall{
        "resources/GandalfHardcore/PC/fall.png",
        _fall_frames,
        _fps
    };
    lib::AnimatedSprite _attack{
        "resources/GandalfHardcore/PC/attack.png",
        _attack_frames,
        _fps
    };
    lib::AnimatedSprite _death{
        "resources/GandalfHardcore/PC/death.png",
        _death_frames,
        _fps
    };

public:
    void draw();
};
