#pragma once
#include "lib/animatedsprite.h"

enum class EvilWizardSprite
{
    attack,
    death,
    fall,
    hit,
    idle,
    jump,
    run,
};

class EvilWizard
{
public:
    EvilWizard() = default;
    EvilWizard(raylib::Vector2 position) : _position(position){};

    void draw();
    void action(EvilWizardSprite action);
    void draw_attack_down();
    void draw_attack_up();
    void draw_death();
    void draw_fall();
    void draw_hit();
    void draw_idle();
    void draw_jump();
    void draw_run();
    void move(raylib::Vector2 position);
    void set_position(raylib::Vector2 position);

    raylib::Vector2 get_position();

private:
    raylib::Vector2  _position{0, 0};
    EvilWizardSprite _sprite{EvilWizardSprite::idle};
    int              _frameno{0};
    bool             _swing_up{false};

    static constexpr int _fps                = 10;
    static constexpr int _attack_down_frames = 8;
    static constexpr int _attack_up_frames   = 8;
    static constexpr int _death_frames       = 7;
    static constexpr int _fall_frames        = 2;
    static constexpr int _hit_frames         = 3;
    static constexpr int _idle_frames        = 8;
    static constexpr int _jump_frames        = 2;
    static constexpr int _run_frames         = 8;

    lib::AnimatedSprite _attack_down{
        "resources/evilwizard2/attack2.png", _attack_down_frames, _fps
    };
    lib::AnimatedSprite _attack_up{
        "resources/evilwizard2/attack1.png", _attack_up_frames, _fps
    };
    lib::AnimatedSprite _death{
        "resources/evilwizard2/death.png", _death_frames, _fps
    };
    lib::AnimatedSprite _fall{
        "resources/evilwizard2/fall.png", _fall_frames, _fps
    };
    lib::AnimatedSprite _hit{
        "resources/evilwizard2/take-hit.png", _hit_frames, _fps
    };
    lib::AnimatedSprite _idle{
        "resources/evilwizard2/idle.png", _idle_frames, _fps
    };
    lib::AnimatedSprite _jump{
        "resources/evilwizard2/jump.png", _jump_frames, _fps
    };
    lib::AnimatedSprite _run{
        "resources/evilwizard2/run.png", _run_frames, _fps
    };
};
