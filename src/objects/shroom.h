#pragma once
#include "lib/animatedsprite.h"
#include "objects/actor.h"
#include <string>

enum class ShroomActs {
    hide,
    idle,
    peek,
    pop,
    walk,
};

inline std::string to_string(ShroomActs sact) {
    switch (sact) {
    case ShroomActs::hide: return "Hide";
    case ShroomActs::idle: return "Idle";
    case ShroomActs::peek: return "Peek";
    case ShroomActs::pop:  return "Pop ";
    case ShroomActs::walk: return "Walk";
	default:               return "    ";
    }
};

class Shroom: public Actor<ShroomActs> {
private:
    int              _tick{0};
    static const int _fps         = 15;
    static const int _idle_frames = 6;
    static const int _hide_frames = 8;
    static const int _peek_frames = 4;
    static const int _pop_frames  = 4;
    static const int _walk_frames = 8;

    lib::AnimatedSprite _idle{"resources/shroom/idle.png", _idle_frames, _fps};
    lib::AnimatedSprite _hide{"resources/shroom/hide.png", _hide_frames, _fps};
    lib::AnimatedSprite _peek{"resources/shroom/peek.png", _peek_frames, _fps};
    lib::AnimatedSprite _pop{"resources/shroom/pop.png", _pop_frames, 1};
    lib::AnimatedSprite _walk{"resources/shroom/walk.png", _walk_frames, _fps};

public:
    void draw();
    void toggle_state();
};
