#include "raylib/ray.h"

raylib::Ray::Ray(const ::Ray& ray) {
    set(ray);
}

raylib::Ray::Ray(::Vector3 _position, ::Vector3 _direction)
    : ::Ray{_position, _direction} {}

raylib::Ray::Ray(::Vector2 mousePosition, const ::Camera& camera) {
    set(::GetMouseRay(mousePosition, camera));
}

raylib::Ray& raylib::Ray::operator=(const ::Ray& ray) {
    set(ray);
    return *this;
}

::Vector3 raylib::Ray::GetPosition() const {
    return position;
}

void raylib::Ray::SetPosition(::Vector3 value) {
    position = value;
}

::Vector3 raylib::Ray::GetDirection() const {
    return direction;
}

void raylib::Ray::SetDirection(::Vector3 value) {
    direction = value;
}

void raylib::Ray::Draw(::Color color) const {
    DrawRay(*this, color);
}

raylib::RayCollision
raylib::Ray::GetCollision(::Vector3 center, float radius) const {
    return RayCollision(::GetRayCollisionSphere(*this, center, radius));
}

raylib::RayCollision raylib::Ray::GetCollision(const ::BoundingBox& box) const {
    return RayCollision(::GetRayCollisionBox(*this, box));
}

raylib::RayCollision
raylib::Ray::GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const {
    return RayCollision(::GetRayCollisionMesh(*this, mesh, transform));
}

raylib::RayCollision raylib::Ray::GetCollision(
    ::Vector3 pnt1,
    ::Vector3 pnt2,
    ::Vector3 pnt3
) const {
    return RayCollision(::GetRayCollisionTriangle(*this, pnt1, pnt2, pnt3));
}

raylib::RayCollision raylib::Ray::GetCollision(
    ::Vector3 pnt1,
    ::Vector3 pnt2,
    ::Vector3 pnt3,
    ::Vector3 pnt4
) const {
    return RayCollision(::GetRayCollisionQuad(*this, pnt1, pnt2, pnt3, pnt4));
}

raylib::Ray
raylib::Ray::GetMouse(::Vector2 mousePosition, const ::Camera& camera) {
    return Ray(::GetMouseRay(mousePosition, camera));
}

raylib::Ray raylib::Ray::GetMouse(const ::Camera& camera) {
    return Ray(::GetMouseRay(::GetMousePosition(), camera));
}

void raylib::Ray::set(const ::Ray& ray) {
    position  = ray.position;
    direction = ray.direction;
}
