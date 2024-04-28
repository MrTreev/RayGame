#include "objects/evilwizard.h"

void
EvilWizard::draw_attack_down(const double time)
{
    _attack1.Draw(_position, time);
};

void
EvilWizard::draw_attack_up(const double time)
{
    _attack2.Draw(_position, time);
};

void
EvilWizard::draw_death(const double time)
{
    _death.Draw(_position, time);
};

void
EvilWizard::draw_fall(const double time)
{
    _fall.Draw(_position, time);
};

void
EvilWizard::draw_hit(const double time)
{
    _hit.Draw(_position, time);
};

void
EvilWizard::draw_idle(const double time)
{
    _idle.Draw(_position, time);
};

void
EvilWizard::draw_jump(const double time)
{
    _jump.Draw(_position, time);
};

void
EvilWizard::draw_run(const double time)
{
    _run.Draw(_position, time);
};
