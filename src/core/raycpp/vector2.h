#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/raymath.h"
#include <string>

namespace core::raycpp {
class Vector2: public ::Vector2 {
public:
    explicit Vector2(const ::Vector2& vec);
    Vector2(float xpos, float ypos);
    explicit Vector2(float xpos);
    Vector2();

    float GetX() const;
    void  SetX(float value);
    float GetY() const;
    void  SetY(float value);

    Vector2&    operator=(const ::Vector2& vector2);
    bool        operator==(const ::Vector2& other) const;
    bool        operator!=(const ::Vector2& other) const;
    std::string ToString() const;
    explicit    operator std::string() const;

#ifndef RAYLIB_CPP_NO_MATH
    Vector2  Add(const ::Vector2& vector2) const;
    Vector2  operator+(const ::Vector2& vector2) const;
    Vector2& operator+=(const ::Vector2& vector2);
    Vector2  Subtract(const ::Vector2& vector2) const;
    Vector2  operator-(const ::Vector2& vector2) const;
    Vector2& operator-=(const ::Vector2& vector2);
    Vector2  Negate() const;
    Vector2  operator-() const;
    Vector2  Multiply(const ::Vector2& vector2) const;
    Vector2  operator*(const ::Vector2& vector2) const;
    Vector2& operator*=(const ::Vector2& vector2);
    Vector2  Scale(const float scale) const;
    Vector2  operator*(const float scale) const;
    Vector2& operator*=(const float scale);
    Vector2  Divide(const ::Vector2& vector2) const;
    Vector2  operator/(const ::Vector2& vector2) const;
    Vector2& operator/=(const ::Vector2& vector2);
    Vector2  Divide(const float div) const;
    Vector2  operator/(const float div) const;
    Vector2& operator/=(const float div);
    Vector2  Normalize() const;
    Vector2  Transform(::Matrix mat) const;
    Vector2  Lerp(const ::Vector2& vector2, float amount) const;
    Vector2  Reflect(const ::Vector2& normal) const;
    Vector2  Rotate(float angle) const;
    Vector2  MoveTowards(const ::Vector2& target, float maxDistance) const;
    Vector2  Invert() const;
    Vector2  Clamp(::Vector2 min, ::Vector2 max) const;
    Vector2  Clamp(float min, float max) const;
    int      Equals(::Vector2 qvec) const;
    float    Length() const;
    float    LengthSqr() const;
    float    DotProduct(const ::Vector2& vector2) const;
    float    Distance(const ::Vector2& vector2) const;
    float    DistanceSqr(::Vector2 vec2) const;
    float    Angle(const ::Vector2& vector2) const;
    static Vector2 Zero();
    static Vector2 One();
#endif

    void DrawPixel(::Color color = {0, 0, 0, 255}) const {
        ::DrawPixelV(*this, color);
    }

    void DrawLine(::Vector2 endPos, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineV(*this, endPos, color);
    }

    void DrawLine(::Vector2 endPos, float thick, ::Color color = {0, 0, 0, 255})
        const {
        ::DrawLineEx(*this, endPos, thick, color);
    }

    void DrawLineBezier(
        ::Vector2 endPos,
        float     thick,
        ::Color   color = {0, 0, 0, 255}
    ) const {
        ::DrawLineBezier(*this, endPos, thick, color);
    }

    void DrawCircle(float radius, ::Color color = {0, 0, 0, 255}) const {
        ::DrawCircleV(*this, radius, color);
    }

    void DrawRectangle(::Vector2 size, ::Color color = {0, 0, 0, 255}) const {
        ::DrawRectangleV(*this, size, color);
    }

    void DrawPoly(
        int     sides,
        float   radius,
        float   rotation,
        ::Color color = {0, 0, 0, 255}
    ) const {
        ::DrawPoly(*this, sides, radius, rotation, color);
    }

    bool CheckCollisionCircle(float radius1, ::Vector2 center2, float radius2)
        const {
        return ::CheckCollisionCircles(*this, radius1, center2, radius2);
    }

    bool CheckCollisionCircle(float radius, ::Rectangle rec) const {
        return ::CheckCollisionCircleRec(*this, radius, rec);
    }

    bool CheckCollision(::Rectangle rec) const {
        return ::CheckCollisionPointRec(*this, rec);
    }

    bool CheckCollision(::Vector2 center, float radius) const {
        return ::CheckCollisionPointCircle(*this, center, radius);
    }

    bool CheckCollision(::Vector2 pnt1, ::Vector2 pnt2, ::Vector2 pnt3) const {
        return ::CheckCollisionPointTriangle(*this, pnt1, pnt2, pnt3);
    }

    bool CheckCollisionLines(
        ::Vector2  endPos1,
        ::Vector2  startPos2,
        ::Vector2  endPos2,
        ::Vector2* collisionPoint
    ) const {
        return ::CheckCollisionLines(
            *this,
            endPos1,
            startPos2,
            endPos2,
            collisionPoint
        );
    }

    bool CheckCollisionPointLine(
        ::Vector2 pnt1,
        ::Vector2 pnt2,
        int       threshold = 1
    ) const {
        return ::CheckCollisionPointLine(*this, pnt1, pnt2, threshold);
    }

protected:
    void set(const ::Vector2& vec);
};

} // namespace core::raycpp
