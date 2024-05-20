#include "core/raycpp/vector4.h"
#include "core/raycpp/raymath.h"

core::raycpp::Vector4::Vector4(const ::Vector4& vec)
    : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

core::raycpp::Vector4::Vector4(float xpos, float ypos, float zpos, float wpos)
    : ::Vector4{xpos, ypos, zpos, wpos} {}

core::raycpp::Vector4::Vector4(float xpos, float ypos, float zpos)
    : ::Vector4{xpos, ypos, zpos, 0} {}

core::raycpp::Vector4::Vector4(float xpos, float ypos)
    : ::Vector4{xpos, ypos, 0, 0} {}

core::raycpp::Vector4::Vector4(float xpos)
    : ::Vector4{xpos, 0, 0, 0} {}

core::raycpp::Vector4::Vector4()
    : ::Vector4{0, 0, 0, 0} {}

core::raycpp::Vector4::Vector4(::Rectangle rectangle)
    : ::Vector4{rectangle.x, rectangle.y, rectangle.width, rectangle.height} {}

core::raycpp::Vector4::Vector4(::Color color) {
    set(ColorNormalize(color));
}

float core::raycpp::Vector4::GetX() const {
    return x;
}

void core::raycpp::Vector4::SetX(float value) {
    x = value;
}

float core::raycpp::Vector4::GetY() const {
    return y;
}

void core::raycpp::Vector4::SetY(float value) {
    y = value;
}

float core::raycpp::Vector4::GetZ() const {
    return z;
}

void core::raycpp::Vector4::SetZ(float value) {
    z = value;
}

float core::raycpp::Vector4::GetW() const {
    return w;
}

void core::raycpp::Vector4::SetW(float value) {
    w = value;
}

core::raycpp::Vector4& core::raycpp::Vector4::operator=(const ::Vector4& vector4) {
    set(vector4);
    return *this;
}

bool core::raycpp::Vector4::operator==(const ::Vector4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool core::raycpp::Vector4::operator!=(const ::Vector4& other) const {
    return !(*this == other);
}

::Rectangle core::raycpp::Vector4::ToRectangle() const {
    return {x, y, z, w};
}

core::raycpp::Vector4::operator ::Rectangle() const {
    return {x, y, z, w};
}

std::string core::raycpp::Vector4::ToString() const {
    return TextFormat("Vector4(%f, %f, %f, %f)", x, y, z, w);
}

core::raycpp::Vector4::operator std::string() const {
    return ToString();
}

void core::raycpp::Vector4::set(const ::Vector4& vec4) {
    x = vec4.x;
    y = vec4.y;
    z = vec4.z;
    w = vec4.w;
}

core::raycpp::Vector4::operator Color() const {
    return ColorFromNormalized();
}

Color core::raycpp::Vector4::ColorFromNormalized() const {
    return ::ColorFromNormalized(*this);
}

#ifndef RAYLIB_CPP_NO_MATH
core::raycpp::Vector4 core::raycpp::Vector4::Multiply(const ::Vector4& vector4) const {
    return Vector4(QuaternionMultiply(*this, vector4));
}

core::raycpp::Vector4 core::raycpp::Vector4::operator*(const ::Vector4& vector4) const {
    return Vector4(QuaternionMultiply(*this, vector4));
}

core::raycpp::Vector4
core::raycpp::Vector4::Lerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionLerp(*this, vector4, amount));
}

core::raycpp::Vector4
core::raycpp::Vector4::Nlerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionNlerp(*this, vector4, amount));
}

core::raycpp::Vector4
core::raycpp::Vector4::Slerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionSlerp(*this, vector4, amount));
}

Matrix core::raycpp::Vector4::ToMatrix() const {
    return QuaternionToMatrix(*this);
}

float core::raycpp::Vector4::Length() const {
    return QuaternionLength(*this);
}

core::raycpp::Vector4 core::raycpp::Vector4::Normalize() const {
    return Vector4(QuaternionNormalize(*this));
}

core::raycpp::Vector4 core::raycpp::Vector4::Invert() const {
    return Vector4(QuaternionInvert(*this));
}

void core::raycpp::Vector4::ToAxisAngle(::Vector3* outAxis, float* outAngle) const {
    QuaternionToAxisAngle(*this, outAxis, outAngle);
}

std::pair<Vector3, float> core::raycpp::Vector4::ToAxisAngle() const {
    Vector3 outAxis;
    float   outAngle = 0;
    QuaternionToAxisAngle(*this, &outAxis, &outAngle);

    return {outAxis, outAngle};
}

core::raycpp::Vector4 core::raycpp::Vector4::Transform(const ::Matrix& matrix) const {
    return Vector4(::QuaternionTransform(*this, matrix));
}

core::raycpp::Vector4 core::raycpp::Vector4::Identity() {
    return Vector4(::QuaternionIdentity());
}

core::raycpp::Vector4 core::raycpp::Vector4::FromVector3ToVector3(
    const ::Vector3& from,
    const ::Vector3& tovec
) {
    return Vector4(::QuaternionFromVector3ToVector3(from, tovec));
}

core::raycpp::Vector4 core::raycpp::Vector4::FromMatrix(const ::Matrix& matrix) {
    return Vector4(::QuaternionFromMatrix(matrix));
}

core::raycpp::Vector4
core::raycpp::Vector4::FromAxisAngle(const ::Vector3& axis, const float angle) {
    return Vector4(::QuaternionFromAxisAngle(axis, angle));
}

core::raycpp::Vector4 core::raycpp::Vector4::FromEuler(
    const float pitch,
    const float yaw,
    const float roll
) {
    return Vector4(::QuaternionFromEuler(pitch, yaw, roll));
}

core::raycpp::Vector4 core::raycpp::Vector4::FromEuler(const ::Vector3& vector3) {
    return Vector4(::QuaternionFromEuler(vector3.x, vector3.y, vector3.z));
}

Vector3 core::raycpp::Vector4::ToEuler() const {
    return ::QuaternionToEuler(*this);
}
#endif
