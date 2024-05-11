#include "raylib/matrix.h"

void raylib::Matrix::set(const ::Matrix& mat) {
    m0  = mat.m0;
    m1  = mat.m1;
    m2  = mat.m2;
    m3  = mat.m3;
    m4  = mat.m4;
    m5  = mat.m5;
    m6  = mat.m6;
    m7  = mat.m7;
    m8  = mat.m8;
    m9  = mat.m9;
    m10 = mat.m10;
    m11 = mat.m11;
    m12 = mat.m12;
    m13 = mat.m13;
    m14 = mat.m14;
    m15 = mat.m15;
}

raylib::Matrix::Matrix(const ::Matrix& mat)
    : ::Matrix{
        mat.m0,
        mat.m4,
        mat.m8,
        mat.m12,
        mat.m1,
        mat.m5,
        mat.m9,
        mat.m13,
        mat.m2,
        mat.m6,
        mat.m10,
        mat.m14,
        mat.m3,
        mat.m7,
        mat.m11,
        mat.m15
    } {}

raylib::Matrix::Matrix(
    float _m0,
    float _m4,
    float _m8,
    float _m12,
    float _m1,
    float _m5,
    float _m9,
    float _m13,
    float _m2,
    float _m6,
    float _m10,
    float _m14,
    float _m3,
    float _m7,
    float _m11,
    float _m15
)
    : ::Matrix{
        _m0,
        _m4,
        _m8,
        _m12,
        _m1,
        _m5,
        _m9,
        _m13,
        _m2,
        _m6,
        _m10,
        _m14,
        _m3,
        _m7,
        _m11,
        _m15
    } {}

float raylib::Matrix::GetM0() const {
    return m0;
}

void raylib::Matrix::SetM0(float value) {
    m0 = value;
}

float raylib::Matrix::GetM1() const {
    return m1;
}

void raylib::Matrix::SetM1(float value) {
    m1 = value;
}

float raylib::Matrix::GetM2() const {
    return m2;
}

void raylib::Matrix::SetM2(float value) {
    m2 = value;
}

float raylib::Matrix::GetM3() const {
    return m3;
}

void raylib::Matrix::SetM3(float value) {
    m3 = value;
}

float raylib::Matrix::GetM4() const {
    return m4;
}

void raylib::Matrix::SetM4(float value) {
    m4 = value;
}

float raylib::Matrix::GetM5() const {
    return m5;
}

void raylib::Matrix::SetM5(float value) {
    m5 = value;
}

float raylib::Matrix::GetM6() const {
    return m6;
}

void raylib::Matrix::SetM6(float value) {
    m6 = value;
}

float raylib::Matrix::GetM7() const {
    return m7;
}

void raylib::Matrix::SetM7(float value) {
    m7 = value;
}

float raylib::Matrix::GetM8() const {
    return m8;
}

void raylib::Matrix::SetM8(float value) {
    m8 = value;
}

float raylib::Matrix::GetM9() const {
    return m9;
}

void raylib::Matrix::SetM9(float value) {
    m9 = value;
}

float raylib::Matrix::GetM10() const {
    return m10;
}

void raylib::Matrix::SetM10(float value) {
    m10 = value;
}

float raylib::Matrix::GetM11() const {
    return m11;
}

void raylib::Matrix::SetM11(float value) {
    m11 = value;
}

float raylib::Matrix::GetM12() const {
    return m12;
}

void raylib::Matrix::SetM12(float value) {
    m12 = value;
}

float raylib::Matrix::GetM13() const {
    return m13;
}

void raylib::Matrix::SetM13(float value) {
    m13 = value;
}

float raylib::Matrix::GetM14() const {
    return m14;
}

void raylib::Matrix::SetM14(float value) {
    m14 = value;
}

float raylib::Matrix::GetM15() const {
    return m15;
}

void raylib::Matrix::SetM15(float value) {
    m15 = value;
}

raylib::Matrix& raylib::Matrix::operator=(const ::Matrix& matrix) {
    set(matrix);
    return *this;
}

bool raylib::Matrix::operator==(const ::Matrix& other) {
    return m0 == other.m0 && m1 == other.m1 && m2 == other.m2 && m3 == other.m3
           && m4 == other.m4 && m5 == other.m5 && m6 == other.m6
           && m7 == other.m7 && m8 == other.m8 && m9 == other.m9
           && m10 == other.m10 && m11 == other.m11 && m12 == other.m12
           && m13 == other.m13 && m14 == other.m14 && m15 == other.m15;
}

bool raylib::Matrix::operator!=(const ::Matrix& other) {
    return !(*this == other);
}

float raylib::Matrix::Trace() const {
    /* (sum of the values along the diagonal) */
    return ::MatrixTrace(*this);
}

raylib::Matrix raylib::Matrix::Transpose() const {
    return raylib::Matrix(::MatrixTranspose(*this));
}

raylib::Matrix raylib::Matrix::Invert() const {
    return raylib::Matrix(::MatrixInvert(*this));
}

raylib::Matrix raylib::Matrix::Identity() {
    return raylib::Matrix(::MatrixIdentity());
}

raylib::Matrix raylib::Matrix::Add(const ::Matrix& right) {
    return raylib::Matrix(::MatrixAdd(*this, right));
}

raylib::Matrix raylib::Matrix::operator+(const ::Matrix& matrix) {
    return raylib::Matrix(::MatrixAdd(*this, matrix));
}

raylib::Matrix raylib::Matrix::Subtract(const ::Matrix& right) {
    return raylib::Matrix(::MatrixSubtract(*this, right));
}

raylib::Matrix raylib::Matrix::operator-(const ::Matrix& matrix) {
    return raylib::Matrix(::MatrixSubtract(*this, matrix));
}

raylib::Matrix
raylib::Matrix::Translate(float xshift, float yshift, float zshift) {
    return raylib::Matrix(::MatrixTranslate(xshift, yshift, zshift));
}

raylib::Matrix raylib::Matrix::Rotate(Vector3 axis, float angle) {
    return raylib::Matrix(::MatrixRotate(axis, angle));
}

raylib::Matrix raylib::Matrix::RotateXYZ(Vector3 angle) {
    return raylib::Matrix(::MatrixRotateXYZ(angle));
}

raylib::Matrix raylib::Matrix::RotateX(float angle) {
    return raylib::Matrix(::MatrixRotateX(angle));
}

raylib::Matrix raylib::Matrix::RotateY(float angle) {
    return raylib::Matrix(::MatrixRotateY(angle));
}

raylib::Matrix raylib::Matrix::RotateZ(float angle) {
    return raylib::Matrix(::MatrixRotateZ(angle));
}

raylib::Matrix raylib::Matrix::Scale(float xscale, float yscale, float zscale) {
    return raylib::Matrix(::MatrixScale(xscale, yscale, zscale));
}

raylib::Matrix raylib::Matrix::Multiply(const ::Matrix& right) const {
    return raylib::Matrix(::MatrixMultiply(*this, right));
}

raylib::Matrix raylib::Matrix::operator*(const ::Matrix& matrix) {
    return raylib::Matrix(::MatrixMultiply(*this, matrix));
}

raylib::Matrix raylib::Matrix::Frustum(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far
) {
    return raylib::Matrix(::MatrixFrustum(left, right, bottom, top, near, far));
}

raylib::Matrix raylib::Matrix::Perspective(
    double fovy,
    double aspect,
    double near,
    double far
) {
    return raylib::Matrix(::MatrixPerspective(fovy, aspect, near, far));
}

raylib::Matrix raylib::Matrix::Ortho(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far
) {
    return raylib::Matrix(::MatrixOrtho(left, right, bottom, top, near, far));
}

raylib::Matrix
raylib::Matrix::LookAt(Vector3 eye, Vector3 target, Vector3 vup) {
    return raylib::Matrix(::MatrixLookAt(eye, target, vup));
}

float16 raylib::Matrix::ToFloatV() const {
    return ::MatrixToFloatV(*this);
}

raylib::Matrix::operator float16() const {
    return ToFloatV();
}

raylib::Matrix&
raylib::Matrix::SetShaderValue(const ::Shader& shader, int uniformLoc) {
    ::SetShaderValueMatrix(shader, uniformLoc, *this);
    return *this;
}

raylib::Matrix raylib::Matrix::GetCamera(const ::Camera& camera) {
    return raylib::Matrix(::GetCameraMatrix(camera));
}

raylib::Matrix raylib::Matrix::GetCamera(const ::Camera2D& camera) {
    return raylib::Matrix(::GetCameraMatrix2D(camera));
}
