#include "raylib/vector4.h"
#include "raylib/raymath.h"

raylib::Vector4::Vector4(const ::Vector4& vec)
    : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

raylib::Vector4::Vector4(float xpos, float ypos, float zpos, float wpos)
    : ::Vector4{xpos, ypos, zpos, wpos} {}

raylib::Vector4::Vector4(float xpos, float ypos, float zpos)
    : ::Vector4{xpos, ypos, zpos, 0} {}

raylib::Vector4::Vector4(float xpos, float ypos)
    : ::Vector4{xpos, ypos, 0, 0} {}

raylib::Vector4::Vector4(float xpos)
    : ::Vector4{xpos, 0, 0, 0} {}

raylib::Vector4::Vector4()
    : ::Vector4{0, 0, 0, 0} {}

raylib::Vector4::Vector4(::Rectangle rectangle)
    : ::Vector4{rectangle.x, rectangle.y, rectangle.width, rectangle.height} {}

raylib::Vector4::Vector4(::Color color) {
    set(ColorNormalize(color));
}

float raylib::Vector4::GetX() const {
    return x;
}

void raylib::Vector4::SetX(float value) {
    x = value;
}

float raylib::Vector4::GetY() const {
    return y;
}

void raylib::Vector4::SetY(float value) {
    y = value;
}

float raylib::Vector4::GetZ() const {
    return z;
}

void raylib::Vector4::SetZ(float value) {
    z = value;
}

float raylib::Vector4::GetW() const {
    return w;
}

void raylib::Vector4::SetW(float value) {
    w = value;
}

raylib::Vector4& raylib::Vector4::operator=(const ::Vector4& vector4) {
    set(vector4);
    return *this;
}

bool raylib::Vector4::operator==(const ::Vector4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool raylib::Vector4::operator!=(const ::Vector4& other) const {
    return !(*this == other);
}

::Rectangle raylib::Vector4::ToRectangle() const {
    return {x, y, z, w};
}

raylib::Vector4::operator ::Rectangle() const {
    return {x, y, z, w};
}

std::string raylib::Vector4::ToString() const {
    return TextFormat("Vector4(%f, %f, %f, %f)", x, y, z, w);
}

raylib::Vector4::operator std::string() const {
    return ToString();
}

void raylib::Vector4::set(const ::Vector4& vec4) {
    x = vec4.x;
    y = vec4.y;
    z = vec4.z;
    w = vec4.w;
}

raylib::Vector4::operator Color() const {
    return ColorFromNormalized();
}

Color raylib::Vector4::ColorFromNormalized() const {
    return ::ColorFromNormalized(*this);
}

#ifndef RAYLIB_CPP_NO_MATH
raylib::Vector4 raylib::Vector4::Multiply(const ::Vector4& vector4) const {
    return Vector4(QuaternionMultiply(*this, vector4));
}

raylib::Vector4 raylib::Vector4::operator*(const ::Vector4& vector4) const {
    return Vector4(QuaternionMultiply(*this, vector4));
}

raylib::Vector4
raylib::Vector4::Lerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionLerp(*this, vector4, amount));
}

raylib::Vector4
raylib::Vector4::Nlerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionNlerp(*this, vector4, amount));
}

raylib::Vector4
raylib::Vector4::Slerp(const ::Vector4& vector4, float amount) const {
    return Vector4(QuaternionSlerp(*this, vector4, amount));
}

Matrix raylib::Vector4::ToMatrix() const {
    return QuaternionToMatrix(*this);
}

float raylib::Vector4::Length() const {
    return QuaternionLength(*this);
}

raylib::Vector4 raylib::Vector4::Normalize() const {
    return Vector4(QuaternionNormalize(*this));
}

raylib::Vector4 raylib::Vector4::Invert() const {
    return Vector4(QuaternionInvert(*this));
}

void raylib::Vector4::ToAxisAngle(::Vector3* outAxis, float* outAngle) const {
    QuaternionToAxisAngle(*this, outAxis, outAngle);
}

std::pair<Vector3, float> raylib::Vector4::ToAxisAngle() const {
    Vector3 outAxis;
    float   outAngle = 0;
    QuaternionToAxisAngle(*this, &outAxis, &outAngle);

    return {outAxis, outAngle};
}

raylib::Vector4 raylib::Vector4::Transform(const ::Matrix& matrix) const {
    return Vector4(::QuaternionTransform(*this, matrix));
}

raylib::Vector4 raylib::Vector4::Identity() {
    return Vector4(::QuaternionIdentity());
}

raylib::Vector4 raylib::Vector4::FromVector3ToVector3(
    const ::Vector3& from,
    const ::Vector3& tovec
) {
    return Vector4(::QuaternionFromVector3ToVector3(from, tovec));
}

raylib::Vector4 raylib::Vector4::FromMatrix(const ::Matrix& matrix) {
    return Vector4(::QuaternionFromMatrix(matrix));
}

raylib::Vector4
raylib::Vector4::FromAxisAngle(const ::Vector3& axis, const float angle) {
    return Vector4(::QuaternionFromAxisAngle(axis, angle));
}

raylib::Vector4 raylib::Vector4::FromEuler(
    const float pitch,
    const float yaw,
    const float roll
) {
    return Vector4(::QuaternionFromEuler(pitch, yaw, roll));
}

raylib::Vector4 raylib::Vector4::FromEuler(const ::Vector3& vector3) {
    return Vector4(::QuaternionFromEuler(vector3.x, vector3.y, vector3.z));
}

Vector3 raylib::Vector4::ToEuler() const {
    return ::QuaternionToEuler(*this);
}
#endif
