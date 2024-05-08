#pragma once

#include "raylib/raylib.h"
#include "raylib/vector3.h"

namespace raylib {
class Camera3D: public ::Camera3D {
public:
    Camera3D(const ::Camera3D& camera);
    Camera3D(
        ::Vector3 _position,
        ::Vector3 _target     = ::Vector3{0.0F, 0.0F, 0.0F},
        ::Vector3 _up         = ::Vector3{0.0F, 1.0F, 0.0F},
        float     _fovy       = 0,
        int       _projection = CAMERA_PERSPECTIVE
    );

    Camera3D();

    Camera3D& operator=(const ::Camera3D& camera);
    Camera3D& BeginMode();
    Camera3D& EndMode();
    Matrix    GetMatrix() const;
    Camera3D& Update(int mode);
    Camera3D& Update(::Vector3 movement, ::Vector3 rotation, float zoom = 1.0F);
    Ray       GetMouseRay(::Vector2 mousePosition) const;
    Vector2   GetWorldToScreen(::Vector3 _position) const;

    void DrawBillboard(
        const ::Texture2D& texture,
        ::Vector3          center,
        float              size,
        ::Color            tint = {255, 255, 255, 255}
    ) const;

    void DrawBillboard(
        const ::Texture2D& texture,
        ::Rectangle        sourceRec,
        ::Vector3          center,
        ::Vector2          size,
        ::Color            tint = {255, 255, 255, 255}
    ) const;

    ::Vector3 GetPosition() const;
    void      SetPosition(::Vector3 value);
    ::Vector3 GetTarget() const;
    void      SetTarget(::Vector3 value);
    ::Vector3 GetUp() const;
    void      SetUp(::Vector3 value);
    float     GetFovy() const;
    void      SetFovy(float value);
    int       GetProjection() const;
    void      SetProjection(int value);

protected:
    void set(const ::Camera3D& camera);
};

} // namespace raylib
