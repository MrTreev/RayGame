#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Vector3: public ::Vector3 {
public:
    Vector3(float xpos, float ypos, float zpos);
    Vector3(float xpos, float ypos);
    Vector3();
    explicit Vector3(const ::Vector3& vec);
    explicit Vector3(float xpos);
    explicit Vector3(::Color color);
    Vector3& operator=(const ::Vector3& vector3);

    float GetX() const;
    void  SetX(float value);
    float GetY() const;
    void  SetY(float value);
    float GetZ() const;
    void  SetZ(float value);
    bool  operator==(const ::Vector3& other) const;
    bool  operator!=(const ::Vector3& other) const;

    std::string ToString() const;
    explicit    operator std::string() const;

#ifndef RAYLIB_CPP_NO_MATH
    Vector3  Add(const ::Vector3& vector3) const;
    Vector3  operator+(const ::Vector3& vector3) const;
    Vector3& operator+=(const ::Vector3& vector3);
    Vector3  Subtract(const ::Vector3& vector3) const;
    Vector3  operator-(const ::Vector3& vector3) const;
    Vector3& operator-=(const ::Vector3& vector3);
    Vector3  Negate() const;
    Vector3  operator-() const;
    Vector3  Multiply(const ::Vector3& vector3) const;
    Vector3  operator*(const ::Vector3& vector3) const;
    Vector3& operator*=(const ::Vector3& vector3);
    Vector3  Scale(float scaler) const;
    Vector3  operator*(float scaler) const;
    Vector3& operator*=(float scaler);
    Vector3  Divide(const ::Vector3& vector3) const;
    Vector3  operator/(const ::Vector3& vector3) const;
    Vector3& operator/=(const ::Vector3& vector3);
    Vector3  Divide(float div) const;
    Vector3  operator/(float div) const;
    Vector3& operator/=(float div);
    float    Length() const;
    float    LengthSqr() const;
    Vector3  Normalize() const;
    float    DotProduct(const ::Vector3& vector3) const;
    float    Distance(const ::Vector3& vector3) const;
    Vector3  Lerp(const ::Vector3& vector3, float amount) const;
    Vector3  CrossProduct(const ::Vector3& vector3) const;
    Vector3  Perpendicular() const;
    Vector3  Project(const ::Vector3& vector3) const;
    Vector3  Reject(const ::Vector3& vector3) const;
    void     OrthoNormalize(::Vector3* vector3);
    Vector3  Transform(const ::Matrix& matrix) const;
    Vector3  RotateByQuaternion(const ::Quaternion& quaternion) const;
    Vector3  Reflect(const ::Vector3& normal) const;
    Vector3  Min(const ::Vector3& vector3) const;
    Vector3  Max(const ::Vector3& vector3) const;

    Vector3 Barycenter(
        const ::Vector3& avec,
        const ::Vector3& bvec,
        const ::Vector3& cvec
    ) const;

    static Vector3 Zero();
    static Vector3 One();
#endif
    void DrawLine3D(const ::Vector3& endPos, ::Color color) const;
    void DrawPoint3D(::Color color) const;
    void DrawCircle3D(
        float            radius,
        const ::Vector3& rotationAxis,
        float            rotationAngle,
        Color            color
    ) const;
    void DrawCube(float width, float height, float length, ::Color color) const;
    void DrawCube(const ::Vector3& size, ::Color color) const;
    void DrawCubeWires(const ::Vector3& size, ::Color color) const;
    void DrawSphere(float radius, ::Color color) const;
    void DrawSphere(float radius, int rings, int slices, ::Color color) const;
    void
    DrawCubeWires(float width, float height, float length, ::Color color) const;
    void
    DrawSphereWires(float radius, int rings, int slices, ::Color color) const;
    void DrawPlane(const ::Vector2& size, ::Color color) const;
    bool CheckCollision(float radius1, const ::Vector3& center2, float radius2)
        const;

    void DrawCylinder(
        float   radiusTop,
        float   radiusBottom,
        float   height,
        int     slices,
        ::Color color
    ) const;
    void DrawCylinderWires(
        float   radiusTop,
        float   radiusBottom,
        float   height,
        int     slices,
        ::Color color
    ) const;

protected:
    void set(const ::Vector3& vec);
};
} // namespace raylib
