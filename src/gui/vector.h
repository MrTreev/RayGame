#pragma once
#include "gui/raylib_include.h"
#include <string>

namespace gui {

class Vec2d {
private:
    ::Vector2 _vector;

public:
    Vec2d(float x_val, float y_val)
        : _vector({x_val, y_val}) {}

    void x(const float& x_val) {
        _vector.x = x_val;
    }

    void y(const float& y_val) {
        _vector.y = y_val;
    }

    bool operator==(const Vec2d& other) const {
        return _vector.x == other.x() && _vector.y == other.y();
    }

    bool operator!=(const Vec2d& other) const {
        return !(*this == other);
    }

    Vec2d operator+(const Vec2d& other) const {
        return add(other);
    }

    Vec2d operator-(const Vec2d& other) const {
        return sub(other);
    }

    Vec2d operator+=(const Vec2d& other) {
        set(add(other).vec());
        return *this;
    }

    Vec2d operator-=(const Vec2d& other) {
        set(sub(other).vec());
        return *this;
    }

    void set(const ::Vector2& vec) {
        _vector.x = vec.x;
        _vector.y = vec.y;
    }

    [[nodiscard]]
    float x() const {
        return _vector.x;
    }

    [[nodiscard]]
    float y() const {
        return _vector.y;
    }

    [[nodiscard]]
    ::Vector2 vec() const {
        return _vector;
    }

    [[nodiscard]]
    std::string to_string() const {
        using std::to_string;
        return {"Vec2d(" + to_string(x()) + ", " + to_string(y()) + ")"};
    }

    [[nodiscard]]
    float length() const {
        return std::sqrt((x() * x()) + (y() * y()));
    }

    [[nodiscard]]
    float length_square() const {
        return ((x() * x()) + (y() * y()));
    }

    [[nodiscard]]
    float dotp(const Vec2d& other) const {
        return std::sqrt((x() * other.x()) + (y() * other.y()));
    }

    [[nodiscard]]
    float dotp_square(const Vec2d& other) const {
        return ((x() * other.x()) + (y() * other.y()));
    }

    [[nodiscard]]
    float distance(const Vec2d& other) const {
        return std::sqrt(
            ((x() - other.x()) * (x() - other.x()))
            + ((y() - other.y()) * (y() - other.y()))
        );
    }

    [[nodiscard]]
    float distance_square(const Vec2d& other) const {
        return ((x() - other.x()) * (x() - other.x()))
               + ((y() - other.y()) * (y() - other.y()));
    }

    [[nodiscard]]
    Vec2d add(const Vec2d& other) const {
        return {_vector.x + other.x(), _vector.y + other.y()};
    }

    [[nodiscard]]
    Vec2d sub(const Vec2d& other) const {
        return {_vector.x - other.x(), _vector.y - other.y()};
    }

    [[nodiscard]]
    Vec2d scale(const float& scale) const {
        return {x() * scale, x() * scale};
    }

    [[nodiscard]]
    Vec2d mult(const Vec2d& other) const {
        return {x() * other.x(), y() * other.y()};
    }

    [[nodiscard]]
    Vec2d negate() const {
        return {-x(), -y()};
    }

    [[nodiscard]]
    Vec2d divide(const Vec2d& other) const {
        return {x() / other.x(), y() / other.y()};
    }
};

class Vec4d {};

} // namespace gui
