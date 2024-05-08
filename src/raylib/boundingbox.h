#pragma once

#include "raylib/raylib.h"

namespace raylib {
class BoundingBox: public ::BoundingBox {
public:
    explicit BoundingBox(const ::BoundingBox& box);
    explicit BoundingBox(const ::Mesh& mesh);
    explicit BoundingBox(::Vector3 minMax = ::Vector3{0.0F, 0.0F, 0.0F});
    BoundingBox(::Vector3 _min, ::Vector3 _max);

    void         Draw(::Color color = {255, 255, 255, 255}) const;
    bool         CheckCollision(const ::BoundingBox& box2) const;
    bool         CheckCollision(::Vector3 center, float radius) const;
    bool         CheckCollision(const ::Ray& ray) const;
    RayCollision GetCollision(const ::Ray& ray) const;

    void      SetMin(::Vector3 value);
    void      SetMax(::Vector3 value);
    ::Vector3 GetMin() const;
    ::Vector3 GetMax() const;

protected:
    void set(const ::BoundingBox& box);
    void set(const ::Vector3& _min, const ::Vector3& _max);
};
} // namespace raylib
