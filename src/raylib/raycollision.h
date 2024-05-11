#pragma once

#include "raylib/raylib.h"

namespace raylib {
class RayCollision: public ::RayCollision {
public:
    explicit RayCollision(const ::RayCollision& ray);
    RayCollision(
        bool      _hit,
        float     _distance,
        ::Vector3 _point,
        ::Vector3 _normal
    );
    RayCollision(const ::Ray& ray, const ::BoundingBox& box);
    RayCollision(
        const ::Ray&    ray,
        const ::Mesh&   mesh,
        const ::Matrix& transform
    );
    RayCollision(
        const ::Ray& ray,
        ::Vector3    vec1,
        ::Vector3    vec2,
        ::Vector3    vec3,
        ::Vector3    vec4
    );
    RayCollision(const ::Ray& ray, ::Vector3 center, float radius);
    RayCollision(
        const ::Ray& ray,
        ::Vector3    vec1,
        ::Vector3    vec2,
        ::Vector3    vec3
    );
    RayCollision& operator=(const ::RayCollision& ray);

    void SetHit(bool value);
    void SetDistance(float value);
    void SetPosition(::Vector3 value);
    void SetNormal(::Vector3 value);

    bool      GetHit() const;
    float     GetDistance() const;
    ::Vector3 GetPosition() const;
    ::Vector3 GetNormal() const;

protected:
    void set(const ::RayCollision& ray);
};
} // namespace raylib
