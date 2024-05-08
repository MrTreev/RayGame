#pragma once

#include "raylib/raycollision.h"
#include "raylib/raylib-cpp-utils.h"
#include "raylib/raylib.h"

namespace raylib {
/**
 * Ray type (useful for raycast)
 */
class Ray: public ::Ray {
public:
    Ray(const ::Ray& ray) {
        set(ray);
    }

    Ray(::Vector3 _position  = {0.0f, 0.0f, 0.0f},
        ::Vector3 _direction = {0.0f, 0.0f, 0.0f})
        : ::Ray{_position, _direction} {
        // Nothing.
    }

    Ray(::Vector2 mousePosition, const ::Camera& camera) {
        set(::GetMouseRay(mousePosition, camera));
    }

    Ray& operator=(const ::Ray& ray) {
        set(ray);
        return *this;
    }

    GETTERSETTER(::Vector3, Position, position)
    GETTERSETTER(::Vector3, Direction, direction)

    /**
     * Draw a ray line
     */
    void Draw(::Color color) const {
        DrawRay(*this, color);
    }

    /**
     * Get collision information between ray and sphere
     */
    RayCollision GetCollision(::Vector3 center, float radius) const {
        return ::GetRayCollisionSphere(*this, center, radius);
    }

    /**
     * Detect collision between ray and box
     */
    RayCollision GetCollision(const ::BoundingBox& box) const {
        return ::GetRayCollisionBox(*this, box);
    }

    /**
     * Get collision information between ray and mesh
     */
    RayCollision
    GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const {
        return ::GetRayCollisionMesh(*this, mesh, transform);
    }

    /**
     * Get collision info between ray and triangle
     */
    RayCollision GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3) const {
        return ::GetRayCollisionTriangle(*this, p1, p2, p3);
    }

    /**
     * Get collision info between ray and quad
     */
    RayCollision
    GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3, ::Vector3 p4) const {
        return ::GetRayCollisionQuad(*this, p1, p2, p3, p4);
    }

    /**
     * Get a ray trace from mouse position
     */
    static Ray GetMouse(::Vector2 mousePosition, const ::Camera& camera) {
        return ::GetMouseRay(mousePosition, camera);
    }

    /**
     * Get a ray trace from mouse position
     */
    static Ray GetMouse(const ::Camera& camera) {
        return ::GetMouseRay(::GetMousePosition(), camera);
    }

protected:
    void set(const ::Ray& ray) {
        position  = ray.position;
        direction = ray.direction;
    }
};
} // namespace raylib
