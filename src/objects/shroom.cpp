#include "objects/shroom.h"
#include "config.h"

void Shroom::draw() {
    const int frameno = static_cast<int>(_ticks / (config::frame_rate / _fps));
    switch (_action) {
    case ShroomActs::idle:
        if (frameno >= _idle_frames) {
            _ticks = 0;
        }
        break;
    case ShroomActs::hide:
        if (frameno >= _hide_frames) {
            _action = ShroomActs::peek;
            _ticks  = 0;
        }
        break;
    case ShroomActs::peek:
        if (frameno >= _peek_frames) {
            _ticks = config::frame_rate / _fps;
        };
        break;
    case ShroomActs::pop:
        if (frameno >= _pop_frames) {
            _action = ShroomActs::idle;
            _ticks  = 0;
        };
        break;
    case ShroomActs::walk:
        if (frameno >= _walk_frames) {
            _action = ShroomActs::idle;
            _ticks  = 0;
        };
        break;
    }
    ++_ticks;
    switch (_action) {
    case ShroomActs::hide: _hide.draw(_position, frameno); return;
    case ShroomActs::idle: _idle.draw(_position, frameno); return;
    case ShroomActs::peek: _peek.draw(_position, frameno); return;
    case ShroomActs::pop:  _pop.draw(_position, frameno); return;
    case ShroomActs::walk: _walk.draw(_position, frameno); return;
    }
};

void Shroom::toggle_state() {
    if (_action == ShroomActs::idle) {
        _ticks  = 0;
        _action = ShroomActs::hide;
        return;
    }
    if (_action == ShroomActs::peek) {
        _ticks  = 0;
        _action = ShroomActs::pop;
        return;
    }
};
