#pragma once
#include "raylib/vector2.h"

template<typename Action_e>
class Actor {
private:
    raylib::Vector2 _position{0, 0};
    Action_e        _action{Action_e::idle};

public:
    explicit Actor(raylib::Vector2 position)
        : _position(position) {}

    explicit Actor(raylib::Vector2 position, Action_e action)
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

    void move(raylib::Vector2 delta) {
        _position += delta;
    }

    void move(float delta_x, float delta_y) {
        _position += {delta_x, delta_y};
    }

    void position(raylib::Vector2 position) {
        _position = position;
    }

    raylib::Vector2 position() {
        return _position;
    }
};
