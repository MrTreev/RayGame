#include <raycpp/Vector2.hpp>

template <typename Action_e>
class Actor
{
protected:
    raylib::Vector2 _position{0, 0};
    Action_e        _action{Action_e::idle};
    int             _ticks{0};

public:
    Actor(raylib::Vector2 position) : _position(position){};

    Actor()                         = default;
    ~Actor()                        = default;
    Actor(const Actor &)            = delete;
    Actor(const Actor &&)           = delete;
    Actor operator=(const Actor &)  = delete;
    Actor operator=(const Actor &&) = delete;

    void draw();

    void
    action(Action_e action)
    {
        if (_action != action)
        {
            _ticks = 0;
        }
        _action = action;
    };

    void
    move(raylib::Vector2 delta)
    {
        _position += delta;
    };

    void
    set_position(raylib::Vector2 position)
    {
        _position = position;
    };

    raylib::Vector2
    get_position()
    {
        return _position;
    };

    void
    reset()
    {
        _action = Action_e::idle;
        _ticks  = 0;
    };
};
