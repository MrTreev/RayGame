#pragma once
#include "core/raycpp/vector2.h"

namespace core {

template<typename Action_e>
class Actor {
private:
    core::raycpp::Vector2 _position{0, 0};
    Action_e        _action{};

public:
    explicit Actor(core::raycpp::Vector2 position)
        : _position(position) {}

    explicit Actor(core::raycpp::Vector2 position, Action_e action)
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

    void move(core::raycpp::Vector2 delta) {
        _position += delta;
    }

    void move(float delta_x, float delta_y) {
        _position += {delta_x, delta_y};
    }

    void position(core::raycpp::Vector2 position) {
        _position = position;
    }

    core::raycpp::Vector2 position() {
        return _position;
    }
};

} // namespace core
