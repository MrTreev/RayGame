#pragma once
#include "lib/animatedsprite.h"

class EvilWizard
{
public:
    EvilWizard() = default;
    EvilWizard(raylib::Vector2 position) : _position(position){};

    void draw_attack_down(const double time);
    void draw_attack_up(const double time);
    void draw_death(const double time);
    void draw_fall(const double time);
    void draw_hit(const double time);
    void draw_idle(const double time);
    void draw_jump(const double time);
    void draw_run(const double time);

    void
    set_position(raylib::Vector2 position)
    {
        _position = position;
    };

    void
    move(raylib::Vector2 position)
    {
        _position += position;
    };

    raylib::Vector2
    get_position()
    {
        return _position;
    };

private:
    raylib::Vector2 _position{0, 0};

    lib::AnimatedSprite _idle{"resources/evilwizard2/idle.png", 8, 10};
    lib::AnimatedSprite _hit{"resources/evilwizard2/take-hit.png", 3, 10};
    lib::AnimatedSprite _attack1{"resources/evilwizard2/attack1.png", 8, 10};
    lib::AnimatedSprite _attack2{"resources/evilwizard2/attack2.png", 8, 10};
    lib::AnimatedSprite _death{"resources/evilwizard2/death.png", 7, 10};
    lib::AnimatedSprite _fall{"resources/evilwizard2/fall.png", 2, 10};
    lib::AnimatedSprite _jump{"resources/evilwizard2/jump.png", 2, 10};
    lib::AnimatedSprite _run{"resources/evilwizard2/run.png", 8, 10};
};
