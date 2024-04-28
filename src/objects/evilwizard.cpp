#include "objects/evilwizard.h"

void
EvilWizard::set_position(raylib::Vector2 position)
{
    _position = position;
};

void
EvilWizard::move(raylib::Vector2 position)
{
    _position += position;
};

raylib::Vector2
EvilWizard::get_position()
{
    return _position;
};

void
EvilWizard::action(EvilWizardSprite action)
{
    _frameno  = 0;
    _sprite   = action;
    _swing_up = !_swing_up;
};

void
EvilWizard::draw_attack_down()
{
    _attack_down.Draw(_position, _frameno);
};

void
EvilWizard::draw_attack_up()
{
    _attack_up.Draw(_position, _frameno);
};

void
EvilWizard::draw_death()
{
    _death.Draw(_position, _frameno);
};

void
EvilWizard::draw_fall()
{
    _fall.Draw(_position, _frameno);
};

void
EvilWizard::draw_hit()
{
    _hit.Draw(_position, _frameno);
};

void
EvilWizard::draw_idle()
{
    _idle.Draw(_position, _frameno);
};

void
EvilWizard::draw_jump()
{
    _jump.Draw(_position, _frameno);
};

void
EvilWizard::draw_run()
{
    _run.Draw(_position, _frameno);
};

void
EvilWizard::draw()
{
    _frameno++;
    switch (_sprite)
    {
        case EvilWizardSprite::attack:
            if (_swing_up)
            {
                draw_attack_up();
                if (_frameno >= _attack_up_frames)
                {
                    _sprite  = EvilWizardSprite::idle;
                    _frameno = 0;
                }
            }
            else
            {
                draw_attack_down();
                if (_frameno >= _attack_down_frames)
                {
                    _sprite  = EvilWizardSprite::idle;
                    _frameno = 0;
                }
            }
            break;
        case EvilWizardSprite::death:
            draw_death();
            if (_frameno >= _death_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
        case EvilWizardSprite::hit:
            draw_hit();
            if (_frameno >= _hit_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
        case EvilWizardSprite::run:
            draw_run();
            if (_frameno >= _run_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
        case EvilWizardSprite::jump:
            draw_jump();
            if (_frameno >= _jump_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
        case EvilWizardSprite::fall:
            draw_fall();
            if (_frameno >= _fall_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
        case EvilWizardSprite::idle:
            draw_idle();
            if (_frameno >= _idle_frames)
            {
                _sprite  = EvilWizardSprite::idle;
                _frameno = 0;
            }
            break;
    }
};
