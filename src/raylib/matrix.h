#pragma once

#include "raylib/raylib.h"
#include "raylib/raymath.h"

namespace raylib {
/* (OpenGL style 4x4 - right handed, column major) */
class Matrix: public ::Matrix {
public:
    Matrix(const ::Matrix& mat);

    Matrix(
        float _m0  = 0,
        float _m4  = 0,
        float _m8  = 0,
        float _m12 = 0,
        float _m1  = 0,
        float _m5  = 0,
        float _m9  = 0,
        float _m13 = 0,
        float _m2  = 0,
        float _m6  = 0,
        float _m10 = 0,
        float _m14 = 0,
        float _m3  = 0,
        float _m7  = 0,
        float _m11 = 0,
        float _m15 = 0
    );

    static Matrix Frustum(
        double left,
        double right,
        double bottom,
        double top,
        double near,
        double far
    );
    static Matrix Ortho(
        double left,
        double right,
        double bottom,
        double top,
        double near,
        double far
    );
    Matrix&       SetShaderValue(const ::Shader& shader, int uniformLoc);
    float16       ToFloatV() const;
    Matrix&       operator=(const ::Matrix& matrix);
    bool          operator==(const ::Matrix& other);
    bool          operator!=(const ::Matrix& other);
    float         Trace() const;
    Matrix        Transpose() const;
    Matrix        Invert() const;
    Matrix        Add(const ::Matrix& right);
    Matrix        operator+(const ::Matrix& matrix);
    Matrix        Subtract(const ::Matrix& right);
    Matrix        operator-(const ::Matrix& matrix);
    Matrix        Multiply(const ::Matrix& right) const;
    Matrix        operator*(const ::Matrix& matrix);
    explicit      operator float16() const;
    static Matrix Translate(float xshift, float yshift, float zshift);
    static Matrix Rotate(Vector3 axis, float angle);
    static Matrix RotateXYZ(Vector3 angle);
    static Matrix RotateX(float angle);
    static Matrix RotateY(float angle);
    static Matrix RotateZ(float angle);
    static Matrix Scale(float xscale, float yscale, float zscale);
    static Matrix LookAt(Vector3 eye, Vector3 target, Vector3 vup);
    static Matrix GetCamera(const ::Camera& camera);
    static Matrix GetCamera(const ::Camera2D& camera);
    static Matrix Identity();
    static Matrix
          Perspective(double fovy, double aspect, double near, double far);
    float GetM0() const;
    float GetM1() const;
    float GetM2() const;
    float GetM3() const;
    float GetM4() const;
    float GetM5() const;
    float GetM6() const;
    float GetM7() const;
    float GetM8() const;
    float GetM9() const;
    float GetM10() const;
    float GetM11() const;
    float GetM12() const;
    float GetM13() const;
    float GetM14() const;
    float GetM15() const;
    void  SetM0(float value);
    void  SetM1(float value);
    void  SetM2(float value);
    void  SetM3(float value);
    void  SetM4(float value);
    void  SetM5(float value);
    void  SetM6(float value);
    void  SetM7(float value);
    void  SetM8(float value);
    void  SetM9(float value);
    void  SetM10(float value);
    void  SetM11(float value);
    void  SetM12(float value);
    void  SetM13(float value);
    void  SetM14(float value);
    void  SetM15(float value);

protected:
    void set(const ::Matrix& mat);
};
} // namespace raylib
