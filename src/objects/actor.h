#pragma once
#include "gui/vector.h"

template<typename Action_e>
class Actor {
private:
    gui::Vec2d _position{0, 0};
    Action_e   _action{Action_e::idle};

public:
    explicit Actor(gui::Vec2d position)
        : _position(position) {}

    explicit Actor(gui::Vec2d position, Action_e action)
        : _position(position)
        , _action(action) {}

    Actor()                        = default;
    ~Actor()                       = default;
    Actor(const Actor&)            = delete;
    Actor(const Actor&&)           = delete;
    Actor operator=(const Actor&)  = delete;
    Actor operator=(const Actor&&) = delete;

    void action(Action_e action) {
        _action = action;
    }

    Action_e action() {
        return _action;
    }

    void move(gui::Vec2d delta) {
        _position += delta;
    }

    void move(float delta_x, float delta_y) {
        _position += {delta_x, delta_y};
    }

    void position(gui::Vec2d position) {
        _position = position;
    }

    gui::Vec2d position() {
        return _position;
    }
};
