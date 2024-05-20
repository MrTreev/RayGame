#include "core/raycpp/ray.h"

core::raycpp::Ray::Ray(const ::Ray& ray) {
    set(ray);
}

core::raycpp::Ray::Ray(::Vector3 _position, ::Vector3 _direction)
    : ::Ray{_position, _direction} {}

core::raycpp::Ray::Ray(::Vector2 mousePosition, const ::Camera& camera) {
    set(::GetMouseRay(mousePosition, camera));
}

core::raycpp::Ray& core::raycpp::Ray::operator=(const ::Ray& ray) {
    set(ray);
    return *this;
}

::Vector3 core::raycpp::Ray::GetPosition() const {
    return position;
}

void core::raycpp::Ray::SetPosition(::Vector3 value) {
    position = value;
}

::Vector3 core::raycpp::Ray::GetDirection() const {
    return direction;
}

void core::raycpp::Ray::SetDirection(::Vector3 value) {
    direction = value;
}

void core::raycpp::Ray::Draw(::Color color) const {
    DrawRay(*this, color);
}

core::raycpp::RayCollision
core::raycpp::Ray::GetCollision(::Vector3 center, float radius) const {
    return RayCollision(::GetRayCollisionSphere(*this, center, radius));
}

core::raycpp::RayCollision core::raycpp::Ray::GetCollision(const ::BoundingBox& box) const {
    return RayCollision(::GetRayCollisionBox(*this, box));
}

core::raycpp::RayCollision
core::raycpp::Ray::GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const {
    return RayCollision(::GetRayCollisionMesh(*this, mesh, transform));
}

core::raycpp::RayCollision core::raycpp::Ray::GetCollision(
    ::Vector3 pnt1,
    ::Vector3 pnt2,
    ::Vector3 pnt3
) const {
    return RayCollision(::GetRayCollisionTriangle(*this, pnt1, pnt2, pnt3));
}

core::raycpp::RayCollision core::raycpp::Ray::GetCollision(
    ::Vector3 pnt1,
    ::Vector3 pnt2,
    ::Vector3 pnt3,
    ::Vector3 pnt4
) const {
    return RayCollision(::GetRayCollisionQuad(*this, pnt1, pnt2, pnt3, pnt4));
}

core::raycpp::Ray
core::raycpp::Ray::GetMouse(::Vector2 mousePosition, const ::Camera& camera) {
    return Ray(::GetMouseRay(mousePosition, camera));
}

core::raycpp::Ray core::raycpp::Ray::GetMouse(const ::Camera& camera) {
    return Ray(::GetMouseRay(::GetMousePosition(), camera));
}

void core::raycpp::Ray::set(const ::Ray& ray) {
    position  = ray.position;
    direction = ray.direction;
}
