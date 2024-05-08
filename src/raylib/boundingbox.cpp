#include "raylib/boundingbox.h"

void raylib::BoundingBox::set(const ::BoundingBox& box) {
    min = box.min;
    max = box.max;
}

void raylib::BoundingBox::set(const ::Vector3& _min, const ::Vector3& _max) {
    min = _min;
    max = _max;
}

raylib::BoundingBox::BoundingBox(const ::BoundingBox& box)
    : ::BoundingBox{box.min, box.max} {}

raylib::BoundingBox::BoundingBox(const ::Mesh& mesh) {
    set(::GetMeshBoundingBox(mesh));
}

raylib::BoundingBox::BoundingBox(::Vector3 minMax)
    : ::BoundingBox{minMax, minMax} {}

raylib::BoundingBox::BoundingBox(::Vector3 _min, ::Vector3 _max)
    : ::BoundingBox{_min, _max} {}

::Vector3 raylib::BoundingBox::GetMin() const {
    return min;
}

void raylib::BoundingBox::SetMin(::Vector3 value) {
    min = value;
}

::Vector3 raylib::BoundingBox::GetMax() const {
    return max;
}

void raylib::BoundingBox::SetMax(::Vector3 value) {
    max = value;
}

void raylib::BoundingBox::Draw(::Color color) const {
    ::DrawBoundingBox(*this, color);
}

bool raylib::BoundingBox::CheckCollision(const ::BoundingBox& box2) const {
    return CheckCollisionBoxes(*this, box2);
}

bool raylib::BoundingBox::CheckCollision(::Vector3 center, float radius) const {
    return CheckCollisionBoxSphere(*this, center, radius);
}

bool raylib::BoundingBox::CheckCollision(const ::Ray& ray) const {
    return GetRayCollisionBox(ray, *this).hit;
}

RayCollision raylib::BoundingBox::GetCollision(const ::Ray& ray) const {
    return GetRayCollisionBox(ray, *this);
}
