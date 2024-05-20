#pragma once

#include "core/raycpp/raycollision.h"
#include "core/raycpp/raylib.h"

namespace core::raycpp {
class Ray: public ::Ray {
public:
    explicit Ray(const ::Ray& ray);
    explicit Ray(
        ::Vector3 _position  = {0.0F, 0.0F, 0.0F},
        ::Vector3 _direction = {0.0F, 0.0F, 0.0F}
    );
    Ray(::Vector2 mousePosition, const ::Camera& camera);
    Ray& operator=(const ::Ray& ray);

    void SetPosition(::Vector3 value);
    void SetDirection(::Vector3 value);
    void Draw(::Color color) const;

    ::Vector3 GetPosition() const;
    ::Vector3 GetDirection() const;

    RayCollision GetCollision(::Vector3 center, float radius) const;
    RayCollision GetCollision(const ::BoundingBox& box) const;
    RayCollision
    GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const;
    RayCollision
    GetCollision(::Vector3 pnt1, ::Vector3 pnt2, ::Vector3 pnt3) const;
    RayCollision
    GetCollision(::Vector3 pnt1, ::Vector3 pnt2, ::Vector3 pnt3, ::Vector3 pnt4)
        const;

    static Ray GetMouse(::Vector2 mousePosition, const ::Camera& camera);
    static Ray GetMouse(const ::Camera& camera);

protected:
    void set(const ::Ray& ray);
};
} // namespace core::raycpp
