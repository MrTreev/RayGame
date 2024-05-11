#pragma once

#ifndef RAYLIB_CPP_NO_MATH
#    include <utility>
#endif

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Vector4: public ::Vector4 {
public:
    Vector4(float xpos, float ypos, float zpos, float wpos);
    Vector4(float xpos, float ypos, float zpos);
    Vector4(float xpos, float ypos);

    explicit Vector4(const ::Vector4& vec);
    explicit Vector4(float xpos);
    explicit Vector4(::Rectangle rectangle);
    explicit Vector4(::Color color);
    explicit operator ::Rectangle() const;
    explicit operator std::string() const;

    Vector4();
    Vector4& operator=(const ::Vector4& vector4);

    float GetX() const;
    void  SetX(float value);
    float GetY() const;
    void  SetY(float value);
    float GetZ() const;
    void  SetZ(float value);
    float GetW() const;
    void  SetW(float value);

    bool operator==(const ::Vector4& other) const;
    bool operator!=(const ::Vector4& other) const;

    ::Rectangle ToRectangle() const;
    std::string ToString() const;

#ifndef RAYLIB_CPP_NO_MATH
    Matrix  ToMatrix() const;
    float   Length() const;
    void    ToAxisAngle(::Vector3* outAxis, float* outAngle) const;
    Vector3 ToEuler() const;

    Vector4 Transform(const ::Matrix& matrix) const;
    Vector4 Multiply(const ::Vector4& vector4) const;
    Vector4 operator*(const ::Vector4& vector4) const;
    Vector4 Lerp(const ::Vector4& vector4, float amount) const;
    Vector4 Nlerp(const ::Vector4& vector4, float amount) const;
    Vector4 Slerp(const ::Vector4& vector4, float amount) const;
    Vector4 Normalize() const;
    Vector4 Invert() const;

    std::pair<Vector3, float> ToAxisAngle() const;

    static Vector4 Identity();
    static Vector4
    FromVector3ToVector3(const ::Vector3& from, const ::Vector3& tovec);
    static Vector4 FromMatrix(const ::Matrix& matrix);
    static Vector4 FromAxisAngle(const ::Vector3& axis, float angle);
    static Vector4 FromEuler(float pitch, float yaw, float roll);
    static Vector4 FromEuler(const ::Vector3& vector3);
#endif
    Color    ColorFromNormalized() const;
    explicit operator Color() const;

protected:
    void set(const ::Vector4& vec4);
};

} // namespace raylib
