#include "raylib/vector3.h"
#include "raylib/raymath.h"
#include <format>

raylib::Vector3::Vector3(const ::Vector3& vec)
    : ::Vector3{vec.x, vec.y, vec.z} {}

raylib::Vector3::Vector3(float xpos, float ypos, float zpos)
    : ::Vector3{xpos, ypos, zpos} {}

raylib::Vector3::Vector3(float xpos, float ypos)
    : ::Vector3{xpos, ypos, 0} {}

raylib::Vector3::Vector3(float xpos)
    : ::Vector3{xpos, 0, 0} {}

raylib::Vector3::Vector3() {}

raylib::Vector3::Vector3(::Color color) {
    set(ColorToHSV(color));
}

raylib::Vector3& raylib::Vector3::operator=(const ::Vector3& vector3) {
    set(vector3);
    return *this;
}

void raylib::Vector3::set(const ::Vector3& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

bool raylib::Vector3::operator==(const ::Vector3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool raylib::Vector3::operator!=(const ::Vector3& other) const {
    return !(*this == other);
}

std::string raylib::Vector3::ToString() const {
    return std::format("Vector3({}, {}, {})", x, y, z);
}

raylib::Vector3::operator std::string() const {
    return ToString();
}

float raylib::Vector3::GetX() const {
    return x;
}

void raylib::Vector3::SetX(float value) {
    x = value;
}

float raylib::Vector3::GetY() const {
    return y;
}

void raylib::Vector3::SetY(float value) {
    y = value;
}

float raylib::Vector3::GetZ() const {
    return z;
}

void raylib::Vector3::SetZ(float value) {
    z = value;
}

void raylib::Vector3::DrawLine3D(const ::Vector3& endPos, ::Color color) const {
    ::DrawLine3D(*this, endPos, color);
}

void raylib::Vector3::DrawPoint3D(::Color color) const {
    ::DrawPoint3D(*this, color);
}

void raylib::Vector3::DrawCircle3D(
    float            radius,
    const ::Vector3& rotationAxis,
    float            rotationAngle,
    Color            color
) const {
    ::DrawCircle3D(*this, radius, rotationAxis, rotationAngle, color);
}

void raylib::Vector3::DrawCube(
    float   width,
    float   height,
    float   length,
    ::Color color
) const {
    ::DrawCube(*this, width, height, length, color);
}

void raylib::Vector3::DrawCube(const ::Vector3& size, ::Color color) const {
    ::DrawCubeV(*this, size, color);
}

void raylib::Vector3::DrawCubeWires(
    float   width,
    float   height,
    float   length,
    ::Color color
) const {
    ::DrawCubeWires(*this, width, height, length, color);
}

void raylib::Vector3::DrawCubeWires(const ::Vector3& size, ::Color color)
    const {
    ::DrawCubeWiresV(*this, size, color);
}

void raylib::Vector3::DrawSphere(float radius, ::Color color) const {
    ::DrawSphere(*this, radius, color);
}

void raylib::Vector3::DrawSphere(
    float   radius,
    int     rings,
    int     slices,
    ::Color color
) const {
    ::DrawSphereEx(*this, radius, rings, slices, color);
}

void raylib::Vector3::DrawSphereWires(
    float   radius,
    int     rings,
    int     slices,
    ::Color color
) const {
    ::DrawSphereWires(*this, radius, rings, slices, color);
}

void raylib::Vector3::DrawCylinder(
    float   radiusTop,
    float   radiusBottom,
    float   height,
    int     slices,
    ::Color color
) const {
    ::DrawCylinder(*this, radiusTop, radiusBottom, height, slices, color);
}

void raylib::Vector3::DrawCylinderWires(
    float   radiusTop,
    float   radiusBottom,
    float   height,
    int     slices,
    ::Color color
) const {
    ::DrawCylinderWires(*this, radiusTop, radiusBottom, height, slices, color);
}

void raylib::Vector3::DrawPlane(const ::Vector2& size, ::Color color) const {
    ::DrawPlane(*this, size, color);
}

bool raylib::Vector3::CheckCollision(
    float            radius1,
    const ::Vector3& center2,
    float            radius2
) const {
    return CheckCollisionSpheres(*this, radius1, center2, radius2);
}

#ifndef RAYLIB_CPP_NO_MATH
raylib::Vector3 raylib::Vector3::Add(const ::Vector3& vector3) const {
    return Vector3(Vector3Add(*this, vector3));
}

raylib::Vector3 raylib::Vector3::operator+(const ::Vector3& vector3) const {
    return Vector3(Vector3Add(*this, vector3));
}

raylib::Vector3& raylib::Vector3::operator+=(const ::Vector3& vector3) {
    set(Vector3Add(*this, vector3));

    return *this;
}

raylib::Vector3 raylib::Vector3::Subtract(const ::Vector3& vector3) const {
    return Vector3(Vector3Subtract(*this, vector3));
}

raylib::Vector3 raylib::Vector3::operator-(const ::Vector3& vector3) const {
    return Vector3(Vector3Subtract(*this, vector3));
}

raylib::Vector3& raylib::Vector3::operator-=(const ::Vector3& vector3) {
    set(Vector3Subtract(*this, vector3));

    return *this;
}

raylib::Vector3 raylib::Vector3::Negate() const {
    return Vector3(Vector3Negate(*this));
}

raylib::Vector3 raylib::Vector3::operator-() const {
    return Vector3(Vector3Negate(*this));
}

raylib::Vector3 raylib::Vector3::Multiply(const ::Vector3& vector3) const {
    return Vector3(Vector3Multiply(*this, vector3));
}

raylib::Vector3 raylib::Vector3::operator*(const ::Vector3& vector3) const {
    return Vector3(Vector3Multiply(*this, vector3));
}

raylib::Vector3& raylib::Vector3::operator*=(const ::Vector3& vector3) {
    set(Vector3Multiply(*this, vector3));

    return *this;
}

raylib::Vector3 raylib::Vector3::Scale(const float scaler) const {
    return Vector3(Vector3Scale(*this, scaler));
}

raylib::Vector3 raylib::Vector3::operator*(const float scaler) const {
    return Vector3(Vector3Scale(*this, scaler));
}

raylib::Vector3& raylib::Vector3::operator*=(const float scaler) {
    set(Vector3Scale(*this, scaler));

    return *this;
}

raylib::Vector3 raylib::Vector3::Divide(const ::Vector3& vector3) const {
    return Vector3(Vector3Divide(*this, vector3));
}

raylib::Vector3 raylib::Vector3::operator/(const ::Vector3& vector3) const {
    return Vector3(Vector3Divide(*this, vector3));
}

raylib::Vector3& raylib::Vector3::operator/=(const ::Vector3& vector3) {
    x /= vector3.x;
    y /= vector3.y;
    z /= vector3.z;

    return *this;
}

raylib::Vector3 raylib::Vector3::Divide(const float div) const {
    return Vector3(::Vector3{x / div, y / div, z / div});
}

raylib::Vector3 raylib::Vector3::operator/(const float div) const {
    return Divide(div);
}

raylib::Vector3& raylib::Vector3::operator/=(const float div) {
    x /= div;
    y /= div;
    z /= div;

    return *this;
}

float raylib::Vector3::Length() const {
    return Vector3Length(*this);
}

float raylib::Vector3::LengthSqr() const {
    return Vector3LengthSqr(*this);
}

raylib::Vector3 raylib::Vector3::Normalize() const {
    return Vector3(Vector3Normalize(*this));
}

float raylib::Vector3::DotProduct(const ::Vector3& vector3) const {
    return Vector3DotProduct(*this, vector3);
}

float raylib::Vector3::Distance(const ::Vector3& vector3) const {
    return Vector3Distance(*this, vector3);
}

raylib::Vector3
raylib::Vector3::Lerp(const ::Vector3& vector3, const float amount) const {
    return Vector3(Vector3Lerp(*this, vector3, amount));
}

raylib::Vector3 raylib::Vector3::CrossProduct(const ::Vector3& vector3) const {
    return Vector3(Vector3CrossProduct(*this, vector3));
}

raylib::Vector3 raylib::Vector3::Perpendicular() const {
    return Vector3(Vector3Perpendicular(*this));
}

raylib::Vector3 raylib::Vector3::Project(const ::Vector3& vector3) const {
    return Vector3(Vector3Project(*this, vector3));
}

raylib::Vector3 raylib::Vector3::Reject(const ::Vector3& vector3) const {
    return Vector3(Vector3Reject(*this, vector3));
}

void raylib::Vector3::OrthoNormalize(::Vector3* vector3) {
    Vector3OrthoNormalize(this, vector3);
}

raylib::Vector3 raylib::Vector3::Transform(const ::Matrix& matrix) const {
    return Vector3(Vector3Transform(*this, matrix));
}

raylib::Vector3
raylib::Vector3::RotateByQuaternion(const ::Quaternion& quaternion) const {
    return Vector3(Vector3RotateByQuaternion(*this, quaternion));
}

raylib::Vector3 raylib::Vector3::Reflect(const ::Vector3& normal) const {
    return Vector3(Vector3Reflect(*this, normal));
}

raylib::Vector3 raylib::Vector3::Min(const ::Vector3& vector3) const {
    return Vector3(Vector3Min(*this, vector3));
}

raylib::Vector3 raylib::Vector3::Max(const ::Vector3& vector3) const {
    return Vector3(Vector3Max(*this, vector3));
}

raylib::Vector3 raylib::Vector3::Barycenter(
    const ::Vector3& avec,
    const ::Vector3& bvec,
    const ::Vector3& cvec
) const {
    return Vector3(Vector3Barycenter(*this, avec, bvec, cvec));
}

raylib::Vector3 raylib::Vector3::Zero() {
    return Vector3(Vector3Zero());
}

raylib::Vector3 raylib::Vector3::One() {
    return Vector3(Vector3One());
}
#endif
