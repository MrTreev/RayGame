#include "core/raycpp/matrix.h"

void core::raycpp::Matrix::set(const ::Matrix& mat) {
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

core::raycpp::Matrix::Matrix(const ::Matrix& mat)
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

core::raycpp::Matrix::Matrix(
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

float core::raycpp::Matrix::GetM0() const {
    return m0;
}

void core::raycpp::Matrix::SetM0(float value) {
    m0 = value;
}

float core::raycpp::Matrix::GetM1() const {
    return m1;
}

void core::raycpp::Matrix::SetM1(float value) {
    m1 = value;
}

float core::raycpp::Matrix::GetM2() const {
    return m2;
}

void core::raycpp::Matrix::SetM2(float value) {
    m2 = value;
}

float core::raycpp::Matrix::GetM3() const {
    return m3;
}

void core::raycpp::Matrix::SetM3(float value) {
    m3 = value;
}

float core::raycpp::Matrix::GetM4() const {
    return m4;
}

void core::raycpp::Matrix::SetM4(float value) {
    m4 = value;
}

float core::raycpp::Matrix::GetM5() const {
    return m5;
}

void core::raycpp::Matrix::SetM5(float value) {
    m5 = value;
}

float core::raycpp::Matrix::GetM6() const {
    return m6;
}

void core::raycpp::Matrix::SetM6(float value) {
    m6 = value;
}

float core::raycpp::Matrix::GetM7() const {
    return m7;
}

void core::raycpp::Matrix::SetM7(float value) {
    m7 = value;
}

float core::raycpp::Matrix::GetM8() const {
    return m8;
}

void core::raycpp::Matrix::SetM8(float value) {
    m8 = value;
}

float core::raycpp::Matrix::GetM9() const {
    return m9;
}

void core::raycpp::Matrix::SetM9(float value) {
    m9 = value;
}

float core::raycpp::Matrix::GetM10() const {
    return m10;
}

void core::raycpp::Matrix::SetM10(float value) {
    m10 = value;
}

float core::raycpp::Matrix::GetM11() const {
    return m11;
}

void core::raycpp::Matrix::SetM11(float value) {
    m11 = value;
}

float core::raycpp::Matrix::GetM12() const {
    return m12;
}

void core::raycpp::Matrix::SetM12(float value) {
    m12 = value;
}

float core::raycpp::Matrix::GetM13() const {
    return m13;
}

void core::raycpp::Matrix::SetM13(float value) {
    m13 = value;
}

float core::raycpp::Matrix::GetM14() const {
    return m14;
}

void core::raycpp::Matrix::SetM14(float value) {
    m14 = value;
}

float core::raycpp::Matrix::GetM15() const {
    return m15;
}

void core::raycpp::Matrix::SetM15(float value) {
    m15 = value;
}

core::raycpp::Matrix& core::raycpp::Matrix::operator=(const ::Matrix& matrix) {
    set(matrix);
    return *this;
}

bool core::raycpp::Matrix::operator==(const ::Matrix& other) {
    return m0 == other.m0 && m1 == other.m1 && m2 == other.m2 && m3 == other.m3
           && m4 == other.m4 && m5 == other.m5 && m6 == other.m6
           && m7 == other.m7 && m8 == other.m8 && m9 == other.m9
           && m10 == other.m10 && m11 == other.m11 && m12 == other.m12
           && m13 == other.m13 && m14 == other.m14 && m15 == other.m15;
}

bool core::raycpp::Matrix::operator!=(const ::Matrix& other) {
    return !(*this == other);
}

float core::raycpp::Matrix::Trace() const {
    /* (sum of the values along the diagonal) */
    return ::MatrixTrace(*this);
}

core::raycpp::Matrix core::raycpp::Matrix::Transpose() const {
    return core::raycpp::Matrix(::MatrixTranspose(*this));
}

core::raycpp::Matrix core::raycpp::Matrix::Invert() const {
    return core::raycpp::Matrix(::MatrixInvert(*this));
}

core::raycpp::Matrix core::raycpp::Matrix::Identity() {
    return core::raycpp::Matrix(::MatrixIdentity());
}

core::raycpp::Matrix core::raycpp::Matrix::Add(const ::Matrix& right) {
    return core::raycpp::Matrix(::MatrixAdd(*this, right));
}

core::raycpp::Matrix core::raycpp::Matrix::operator+(const ::Matrix& matrix) {
    return core::raycpp::Matrix(::MatrixAdd(*this, matrix));
}

core::raycpp::Matrix core::raycpp::Matrix::Subtract(const ::Matrix& right) {
    return core::raycpp::Matrix(::MatrixSubtract(*this, right));
}

core::raycpp::Matrix core::raycpp::Matrix::operator-(const ::Matrix& matrix) {
    return core::raycpp::Matrix(::MatrixSubtract(*this, matrix));
}

core::raycpp::Matrix
core::raycpp::Matrix::Translate(float xshift, float yshift, float zshift) {
    return core::raycpp::Matrix(::MatrixTranslate(xshift, yshift, zshift));
}

core::raycpp::Matrix core::raycpp::Matrix::Rotate(Vector3 axis, float angle) {
    return core::raycpp::Matrix(::MatrixRotate(axis, angle));
}

core::raycpp::Matrix core::raycpp::Matrix::RotateXYZ(Vector3 angle) {
    return core::raycpp::Matrix(::MatrixRotateXYZ(angle));
}

core::raycpp::Matrix core::raycpp::Matrix::RotateX(float angle) {
    return core::raycpp::Matrix(::MatrixRotateX(angle));
}

core::raycpp::Matrix core::raycpp::Matrix::RotateY(float angle) {
    return core::raycpp::Matrix(::MatrixRotateY(angle));
}

core::raycpp::Matrix core::raycpp::Matrix::RotateZ(float angle) {
    return core::raycpp::Matrix(::MatrixRotateZ(angle));
}

core::raycpp::Matrix core::raycpp::Matrix::Scale(float xscale, float yscale, float zscale) {
    return core::raycpp::Matrix(::MatrixScale(xscale, yscale, zscale));
}

core::raycpp::Matrix core::raycpp::Matrix::Multiply(const ::Matrix& right) const {
    return core::raycpp::Matrix(::MatrixMultiply(*this, right));
}

core::raycpp::Matrix core::raycpp::Matrix::operator*(const ::Matrix& matrix) {
    return core::raycpp::Matrix(::MatrixMultiply(*this, matrix));
}

core::raycpp::Matrix core::raycpp::Matrix::Frustum(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far
) {
    return core::raycpp::Matrix(::MatrixFrustum(left, right, bottom, top, near, far));
}

core::raycpp::Matrix core::raycpp::Matrix::Perspective(
    double fovy,
    double aspect,
    double near,
    double far
) {
    return core::raycpp::Matrix(::MatrixPerspective(fovy, aspect, near, far));
}

core::raycpp::Matrix core::raycpp::Matrix::Ortho(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far
) {
    return core::raycpp::Matrix(::MatrixOrtho(left, right, bottom, top, near, far));
}

core::raycpp::Matrix
core::raycpp::Matrix::LookAt(Vector3 eye, Vector3 target, Vector3 vup) {
    return core::raycpp::Matrix(::MatrixLookAt(eye, target, vup));
}

float16 core::raycpp::Matrix::ToFloatV() const {
    return ::MatrixToFloatV(*this);
}

core::raycpp::Matrix::operator float16() const {
    return ToFloatV();
}

core::raycpp::Matrix&
core::raycpp::Matrix::SetShaderValue(const ::Shader& shader, int uniformLoc) {
    ::SetShaderValueMatrix(shader, uniformLoc, *this);
    return *this;
}

core::raycpp::Matrix core::raycpp::Matrix::GetCamera(const ::Camera& camera) {
    return core::raycpp::Matrix(::GetCameraMatrix(camera));
}

core::raycpp::Matrix core::raycpp::Matrix::GetCamera(const ::Camera2D& camera) {
    return core::raycpp::Matrix(::GetCameraMatrix2D(camera));
}
