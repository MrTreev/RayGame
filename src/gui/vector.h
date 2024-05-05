#pragma once
#include "gui/raylib_include.h"
#include <cmath>
#include <concepts>
#include <string>

namespace gui {

namespace {

template<typename Vec>
concept bool Dim3 = requires (Vec vec) { {vec._z} -> float };

template<typename vector_t>
class BaseVector {
private:
    vector_t _vector;

public:
    template<class... Args>
    BaseVector(Args... args){};

    explicit BaseVector(const vector_t& other)
        : _vector(other.vec()){};

    [[nodiscard]]
    float x() const {
        return _vector.x;
    };

    [[nodiscard]]
    float y() const {
        return _vector.y;
    };

    [[nodiscard]]
    vector_t vec() const {
        return _vector;
    };

    void x(const float& x_val) {
        _vector.x = x_val;
    };

    void y(const float& y_val) {
        _vector.y = y_val;
    };
};
} // namespace

class Vec2d: public BaseVector<::Vector2> {
public:
    Vec2d(float x_val, float y_val)
        : _vector({x_val, y_val}){};

    Vec2d& operator=(const Vec2d& other) {
        set(other.vec());
        return *this;
    }

    ::Vector2 Vector2() {
        return _vector;
    }

    [[nodiscard]]
    std::string ToString() const {
        using std::to_string;
        return "Vector2(" + to_string(x()) + ", " + to_string(y()) + ")";
    }

    [[nodiscard]]
    float length() const {
        return std::sqrt((x() * x()) + (y() * y()));
    };

    [[nodiscard]]
    float length_square() const {
        return ((x() * x()) + (y() * y()));
    };

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
    };

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

    [[nodiscard]]
    Vec2d normalise() const {
        Vec2d result = {0, 0};
        float length = sqrtf((x() * x()) + (y() * y()));

        if (length > 0) {
            float ilength = 1.0F / length;
            result.x(x() * ilength);
            result.y(y() * ilength);
        }

        return result;
    }

    bool operator==(const Vec2d& other) const {
        return _vector.x == other.x() && _vector.y == other.y();
    }

    bool operator!=(const Vec2d& other) const {
        return !(*this == other);
    }

    Vec2d operator+(const Vec2d& other) const {
        return add(other);
    };

    Vec2d operator-(const Vec2d& other) const {
        return sub(other);
    };

    Vec2d operator+=(const Vec2d& other) {
        set(add(other).vec());
        return *this;
    };

    Vec2d operator-=(const Vec2d& other) {
        set(sub(other).vec());
        return *this;
    };

private:
    void set(const ::Vector2& vec) {
        _vector.x = vec.x;
        _vector.y = vec.y;
    }
};

class Vec4d {};

} // namespace gui
