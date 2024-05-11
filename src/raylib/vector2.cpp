#include "raylib/vector2.h"
#include <format>

raylib::Vector2::Vector2(const ::Vector2& vec)
    : ::Vector2{vec.x, vec.y} {}

raylib::Vector2::Vector2(float xpos, float ypos)
    : ::Vector2{xpos, ypos} {}

raylib::Vector2::Vector2(float xpos)
    : ::Vector2{xpos, 0} {}

raylib::Vector2::Vector2()
    : ::Vector2{0, 0} {}

raylib::Vector2& raylib::Vector2::operator=(const ::Vector2& vector2) {
    set(vector2);
    return *this;
}

std::string raylib::Vector2::ToString() const {
    return std::format("Vector2({}, {})", x, y);
}

raylib::Vector2::operator std::string() const {
    return ToString();
}

void raylib::Vector2::set(const ::Vector2& vec) {
    x = vec.x;
    y = vec.y;
}

float raylib::Vector2::GetX() const {
    return x;
}

void raylib::Vector2::SetX(float value) {
    x = value;
}

float raylib::Vector2::GetY() const {
    return y;
}

void raylib::Vector2::SetY(float value) {
    y = value;
}

bool raylib::Vector2::operator==(const ::Vector2& other) const {
    return x == other.x && y == other.y;
}

bool raylib::Vector2::operator!=(const ::Vector2& other) const {
    return !(*this == other);
}

raylib::Vector2 raylib::Vector2::Add(const ::Vector2& vector2) const {
    return Vector2(Vector2Add(*this, vector2));
}

raylib::Vector2 raylib::Vector2::operator+(const ::Vector2& vector2) const {
    return Vector2(Vector2Add(*this, vector2));
}

raylib::Vector2& raylib::Vector2::operator+=(const ::Vector2& vector2) {
    set(Vector2Add(*this, vector2));

    return *this;
}

raylib::Vector2 raylib::Vector2::Subtract(const ::Vector2& vector2) const {
    return Vector2(Vector2Subtract(*this, vector2));
}

raylib::Vector2 raylib::Vector2::operator-(const ::Vector2& vector2) const {
    return Vector2(Vector2Subtract(*this, vector2));
}

raylib::Vector2& raylib::Vector2::operator-=(const ::Vector2& vector2) {
    set(Vector2Subtract(*this, vector2));

    return *this;
}

raylib::Vector2 raylib::Vector2::Negate() const {
    return Vector2(Vector2Negate(*this));
}

raylib::Vector2 raylib::Vector2::operator-() const {
    return Vector2(Vector2Negate(*this));
}

raylib::Vector2 raylib::Vector2::Multiply(const ::Vector2& vector2) const {
    return Vector2(Vector2Multiply(*this, vector2));
}

raylib::Vector2 raylib::Vector2::operator*(const ::Vector2& vector2) const {
    return Vector2(Vector2Multiply(*this, vector2));
}

raylib::Vector2& raylib::Vector2::operator*=(const ::Vector2& vector2) {
    set(Vector2Multiply(*this, vector2));

    return *this;
}

raylib::Vector2 raylib::Vector2::Scale(const float scale) const {
    return Vector2(Vector2Scale(*this, scale));
}

raylib::Vector2 raylib::Vector2::operator*(const float scale) const {
    return Vector2(Vector2Scale(*this, scale));
}

raylib::Vector2& raylib::Vector2::operator*=(const float scale) {
    set(Vector2Scale(*this, scale));

    return *this;
}

raylib::Vector2 raylib::Vector2::Divide(const ::Vector2& vector2) const {
    return Vector2(Vector2Divide(*this, vector2));
}

raylib::Vector2 raylib::Vector2::operator/(const ::Vector2& vector2) const {
    return Vector2(Vector2Divide(*this, vector2));
}

raylib::Vector2& raylib::Vector2::operator/=(const ::Vector2& vector2) {
    set(Vector2Divide(*this, vector2));

    return *this;
}

raylib::Vector2 raylib::Vector2::Divide(const float div) const {
    return {x / div, y / div};
}

raylib::Vector2 raylib::Vector2::operator/(const float div) const {
    return Divide(div);
}

raylib::Vector2& raylib::Vector2::operator/=(const float div) {
    this->x /= div;
    this->y /= div;

    return *this;
}

raylib::Vector2 raylib::Vector2::Normalize() const {
    return Vector2(Vector2Normalize(*this));
}

raylib::Vector2 raylib::Vector2::Transform(::Matrix mat) const {
    return Vector2(::Vector2Transform(*this, mat));
}

raylib::Vector2
raylib::Vector2::Lerp(const ::Vector2& vector2, float amount) const {
    return Vector2(Vector2Lerp(*this, vector2, amount));
}

raylib::Vector2 raylib::Vector2::Reflect(const ::Vector2& normal) const {
    return Vector2(Vector2Reflect(*this, normal));
}

raylib::Vector2 raylib::Vector2::Rotate(float angle) const {
    return Vector2(Vector2Rotate(*this, angle));
}

raylib::Vector2
raylib::Vector2::MoveTowards(const ::Vector2& target, float maxDistance) const {
    return Vector2(Vector2MoveTowards(*this, target, maxDistance));
}

raylib::Vector2 raylib::Vector2::Invert() const {
    return Vector2(::Vector2Invert(*this));
}

raylib::Vector2 raylib::Vector2::Clamp(::Vector2 min, ::Vector2 max) const {
    return Vector2(::Vector2Clamp(*this, min, max));
}

raylib::Vector2 raylib::Vector2::Clamp(float min, float max) const {
    return Vector2(::Vector2ClampValue(*this, min, max));
}

int raylib::Vector2::Equals(::Vector2 qvec) const {
    return Vector2Equals(*this, qvec);
}

float raylib::Vector2::Length() const {
    return Vector2Length(*this);
}

float raylib::Vector2::LengthSqr() const {
    return Vector2LengthSqr(*this);
}

float raylib::Vector2::DotProduct(const ::Vector2& vector2) const {
    return Vector2DotProduct(*this, vector2);
}

float raylib::Vector2::Distance(const ::Vector2& vector2) const {
    return Vector2Distance(*this, vector2);
}

float raylib::Vector2::DistanceSqr(::Vector2 vec2) const {
    return ::Vector2DistanceSqr(*this, vec2);
}

float raylib::Vector2::Angle(const ::Vector2& vector2) const {
    return Vector2Angle(*this, vector2);
}

raylib::Vector2 raylib::Vector2::Zero() {
    return Vector2(Vector2Zero());
}

raylib::Vector2 raylib::Vector2::One() {
    return Vector2(Vector2One());
}
