#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/vector2.h"

namespace core::raycpp {

class Camera2D: public ::Camera2D {
public:
    Camera2D();
    Camera2D(const ::Camera2D& camera); //NOLINT: hicpp-explicit-conversion
    Camera2D(
        ::Vector2 _offset,
        ::Vector2 _target,
        float     _rotation = 0.0F,
        float     _zoom     = 1.0F
    );

    void        BeginMode();
    static void EndMode();

    Camera2D& operator=(const ::Camera2D& camera);
    void      SetOffset(::Vector2 value);
    void      SetRotation(float value);
    void      SetTarget(::Vector2 value);
    void      SetZoom(float value);
    Vector2   GetScreenToWorld(::Vector2 position) const;
    Vector2   GetWorldToScreen(::Vector2 position) const;
    ::Vector2 GetOffset() const;
    ::Vector2 GetTarget() const;
    float     GetRotation() const;
    float     GetZoom() const;
    Matrix    GetMatrix() const;

protected:
    void set(const ::Camera2D& camera);
};

} // namespace core::raycpp
