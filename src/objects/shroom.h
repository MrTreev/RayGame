#pragma once
#include "lib/animatedsprite.h"
#include "objects/actor.h"

enum class ShroomActs
{
    hide,
    idle,
    peek,
    pop,
    walk,
};

class Shroom : public Actor<ShroomActs>
{
private:
    static const int _fps         = 10;
    static const int _idle_frames = 6;
    static const int _hide_frames = 8;
    static const int _peek_frames = 4;
    static const int _pop_frames  = 4;
    static const int _walk_frames = 8;

    lib::AnimatedSprite _idle{"resources/shroom/idle.png", _idle_frames, _fps};
    lib::AnimatedSprite _hide{"resources/shroom/hide.png", _hide_frames, _fps};
    lib::AnimatedSprite _peek{"resources/shroom/peek.png", _peek_frames, _fps};
    lib::AnimatedSprite _pop{"resources/shroom/pop.png", _pop_frames, _fps};
    lib::AnimatedSprite _walk{"resources/shroom/walk.png", _walk_frames, _fps};

public:
    void draw();
};
