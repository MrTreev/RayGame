#include "objects/shroom.h"
#include "config.h"
#include "utils/logger.h"

void
Shroom::draw()
{
    ++_ticks;
    const int frameno = static_cast<int>(_ticks / (config::frame_rate / _fps));
    utils::log::info("frameno: " + std::to_string(frameno));
    switch (_action)
    {
        case ShroomActs::idle:
            _idle.Draw(_position, frameno);
            if (frameno >= _idle_frames)
            {
                reset();
            }
            break;
        case ShroomActs::hide:
            _hide.Draw(_position, frameno);
            if (frameno >= _hide_frames)
            {
                _action = ShroomActs::peek;
                _ticks  = 0;
            }
            break;
        case ShroomActs::peek:
            _peek.Draw(_position, frameno);
            if (frameno >= _peek_frames)
            {
                _action = ShroomActs::pop;
                _ticks  = 0;
            };
            break;
        case ShroomActs::pop:
            _pop.Draw(_position, frameno);
            if (frameno >= _pop_frames)
            {
                reset();
            };
            break;
        case ShroomActs::walk:
            _walk.Draw(_position, frameno);
            if (frameno >= _walk_frames)
            {
                reset();
            };
            break;
    }
};
