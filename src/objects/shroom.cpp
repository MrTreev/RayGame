#include "objects/shroom.h"
#include "config.h"

void Shroom::draw() {
    const int frameno = static_cast<int>(_tick / (config::frame_rate / _fps));
    switch (action()) {
    case ShroomActs::idle:
        if (frameno >= _idle_frames) {
            _tick = 0;
        }
        break;
    case ShroomActs::hide:
        if (frameno >= _hide_frames) {
            action(ShroomActs::peek);
            _tick = 0;
        }
        break;
    case ShroomActs::peek:
        if (frameno >= _peek_frames) {
            _tick = config::frame_rate / _fps;
        };
        break;
    case ShroomActs::pop:
        if (frameno >= _pop_frames) {
            action(ShroomActs::idle);
            _tick = 0;
        };
        break;
    case ShroomActs::walk:
        if (frameno >= _walk_frames) {
            action(ShroomActs::idle);
            _tick = 0;
        };
        break;
    }
    ++_tick;
    switch (action()) {
    case ShroomActs::hide: _hide.draw(position(), frameno); break;
    case ShroomActs::idle: _idle.draw(position(), frameno); break;
    case ShroomActs::peek: _peek.draw(position(), frameno); break;
    case ShroomActs::pop:  _pop.draw(position(), frameno); break;
    case ShroomActs::walk: _walk.draw(position(), frameno); break;
    }
}

void Shroom::toggle_state() {
    if (action() == ShroomActs::idle) {
        _tick = 0;
        action(ShroomActs::hide);
        return;
    }
    if (action() == ShroomActs::peek) {
        _tick = 0;
        action(ShroomActs::pop);
        return;
    }
}
