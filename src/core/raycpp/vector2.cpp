#include "core/raycpp/vector2.h"
#include <format>

core::raycpp::Vector2::Vector2(const ::Vector2& vec)
    : ::Vector2{vec.x, vec.y} {}

core::raycpp::Vector2::Vector2(float xpos, float ypos)
    : ::Vector2{xpos, ypos} {}

core::raycpp::Vector2::Vector2(float xpos)
    : ::Vector2{xpos, 0} {}

core::raycpp::Vector2::Vector2()
    : ::Vector2{0, 0} {}

core::raycpp::Vector2& core::raycpp::Vector2::operator=(const ::Vector2& vector2) {
    set(vector2);
    return *this;
}

std::string core::raycpp::Vector2::ToString() const {
    return std::format("Vector2({}, {})", x, y);
}

core::raycpp::Vector2::operator std::string() const {
    return ToString();
}

void core::raycpp::Vector2::set(const ::Vector2& vec) {
    x = vec.x;
    y = vec.y;
}

float core::raycpp::Vector2::GetX() const {
    return x;
}

void core::raycpp::Vector2::SetX(float value) {
    x = value;
}

float core::raycpp::Vector2::GetY() const {
    return y;
}

void core::raycpp::Vector2::SetY(float value) {
    y = value;
}

bool core::raycpp::Vector2::operator==(const ::Vector2& other) const {
    return x == other.x && y == other.y;
}

bool core::raycpp::Vector2::operator!=(const ::Vector2& other) const {
    return !(*this == other);
}

core::raycpp::Vector2 core::raycpp::Vector2::Add(const ::Vector2& vector2) const {
    return Vector2(Vector2Add(*this, vector2));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator+(const ::Vector2& vector2) const {
    return Vector2(Vector2Add(*this, vector2));
}

core::raycpp::Vector2& core::raycpp::Vector2::operator+=(const ::Vector2& vector2) {
    set(Vector2Add(*this, vector2));

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Subtract(const ::Vector2& vector2) const {
    return Vector2(Vector2Subtract(*this, vector2));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator-(const ::Vector2& vector2) const {
    return Vector2(Vector2Subtract(*this, vector2));
}

core::raycpp::Vector2& core::raycpp::Vector2::operator-=(const ::Vector2& vector2) {
    set(Vector2Subtract(*this, vector2));

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Negate() const {
    return Vector2(Vector2Negate(*this));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator-() const {
    return Vector2(Vector2Negate(*this));
}

core::raycpp::Vector2 core::raycpp::Vector2::Multiply(const ::Vector2& vector2) const {
    return Vector2(Vector2Multiply(*this, vector2));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator*(const ::Vector2& vector2) const {
    return Vector2(Vector2Multiply(*this, vector2));
}

core::raycpp::Vector2& core::raycpp::Vector2::operator*=(const ::Vector2& vector2) {
    set(Vector2Multiply(*this, vector2));

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Scale(const float scale) const {
    return Vector2(Vector2Scale(*this, scale));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator*(const float scale) const {
    return Vector2(Vector2Scale(*this, scale));
}

core::raycpp::Vector2& core::raycpp::Vector2::operator*=(const float scale) {
    set(Vector2Scale(*this, scale));

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Divide(const ::Vector2& vector2) const {
    return Vector2(Vector2Divide(*this, vector2));
}

core::raycpp::Vector2 core::raycpp::Vector2::operator/(const ::Vector2& vector2) const {
    return Vector2(Vector2Divide(*this, vector2));
}

core::raycpp::Vector2& core::raycpp::Vector2::operator/=(const ::Vector2& vector2) {
    set(Vector2Divide(*this, vector2));

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Divide(const float div) const {
    return {x / div, y / div};
}

core::raycpp::Vector2 core::raycpp::Vector2::operator/(const float div) const {
    return Divide(div);
}

core::raycpp::Vector2& core::raycpp::Vector2::operator/=(const float div) {
    this->x /= div;
    this->y /= div;

    return *this;
}

core::raycpp::Vector2 core::raycpp::Vector2::Normalize() const {
    return Vector2(Vector2Normalize(*this));
}

core::raycpp::Vector2 core::raycpp::Vector2::Transform(::Matrix mat) const {
    return Vector2(::Vector2Transform(*this, mat));
}

core::raycpp::Vector2
core::raycpp::Vector2::Lerp(const ::Vector2& vector2, float amount) const {
    return Vector2(Vector2Lerp(*this, vector2, amount));
}

core::raycpp::Vector2 core::raycpp::Vector2::Reflect(const ::Vector2& normal) const {
    return Vector2(Vector2Reflect(*this, normal));
}

core::raycpp::Vector2 core::raycpp::Vector2::Rotate(float angle) const {
    return Vector2(Vector2Rotate(*this, angle));
}

core::raycpp::Vector2
core::raycpp::Vector2::MoveTowards(const ::Vector2& target, float maxDistance) const {
    return Vector2(Vector2MoveTowards(*this, target, maxDistance));
}

core::raycpp::Vector2 core::raycpp::Vector2::Invert() const {
    return Vector2(::Vector2Invert(*this));
}

core::raycpp::Vector2 core::raycpp::Vector2::Clamp(::Vector2 min, ::Vector2 max) const {
    return Vector2(::Vector2Clamp(*this, min, max));
}

core::raycpp::Vector2 core::raycpp::Vector2::Clamp(float min, float max) const {
    return Vector2(::Vector2ClampValue(*this, min, max));
}

int core::raycpp::Vector2::Equals(::Vector2 qvec) const {
    return Vector2Equals(*this, qvec);
}

float core::raycpp::Vector2::Length() const {
    return Vector2Length(*this);
}

float core::raycpp::Vector2::LengthSqr() const {
    return Vector2LengthSqr(*this);
}

float core::raycpp::Vector2::DotProduct(const ::Vector2& vector2) const {
    return Vector2DotProduct(*this, vector2);
}

float core::raycpp::Vector2::Distance(const ::Vector2& vector2) const {
    return Vector2Distance(*this, vector2);
}

float core::raycpp::Vector2::DistanceSqr(::Vector2 vec2) const {
    return ::Vector2DistanceSqr(*this, vec2);
}

float core::raycpp::Vector2::Angle(const ::Vector2& vector2) const {
    return Vector2Angle(*this, vector2);
}

core::raycpp::Vector2 core::raycpp::Vector2::Zero() {
    return Vector2(Vector2Zero());
}

core::raycpp::Vector2 core::raycpp::Vector2::One() {
    return Vector2(Vector2One());
}
