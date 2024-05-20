#include "core/raycpp/boundingbox.h"

void core::raycpp::BoundingBox::set(const ::BoundingBox& box) {
    min = box.min;
    max = box.max;
}

void core::raycpp::BoundingBox::set(const ::Vector3& _min, const ::Vector3& _max) {
    min = _min;
    max = _max;
}

core::raycpp::BoundingBox::BoundingBox(const ::BoundingBox& box)
    : ::BoundingBox{box.min, box.max} {}

core::raycpp::BoundingBox::BoundingBox(const ::Mesh& mesh) {
    set(::GetMeshBoundingBox(mesh));
}

core::raycpp::BoundingBox::BoundingBox(::Vector3 minMax)
    : ::BoundingBox{minMax, minMax} {}

core::raycpp::BoundingBox::BoundingBox(::Vector3 _min, ::Vector3 _max)
    : ::BoundingBox{_min, _max} {}

::Vector3 core::raycpp::BoundingBox::GetMin() const {
    return min;
}

void core::raycpp::BoundingBox::SetMin(::Vector3 value) {
    min = value;
}

::Vector3 core::raycpp::BoundingBox::GetMax() const {
    return max;
}

void core::raycpp::BoundingBox::SetMax(::Vector3 value) {
    max = value;
}

void core::raycpp::BoundingBox::Draw(::Color color) const {
    ::DrawBoundingBox(*this, color);
}

bool core::raycpp::BoundingBox::CheckCollision(const ::BoundingBox& box2) const {
    return CheckCollisionBoxes(*this, box2);
}

bool core::raycpp::BoundingBox::CheckCollision(::Vector3 center, float radius) const {
    return CheckCollisionBoxSphere(*this, center, radius);
}

bool core::raycpp::BoundingBox::CheckCollision(const ::Ray& ray) const {
    return GetRayCollisionBox(ray, *this).hit;
}

RayCollision core::raycpp::BoundingBox::GetCollision(const ::Ray& ray) const {
    return GetRayCollisionBox(ray, *this);
}
