#include "raylib/raycollision.h"

raylib::RayCollision::RayCollision(const ::RayCollision& ray) {
    set(ray);
}

raylib::RayCollision::RayCollision(
    bool      _hit,
    float     _distance,
    ::Vector3 _point,
    ::Vector3 _normal
)
    : ::RayCollision{_hit, _distance, _point, _normal} {
    // Nothing.
}

raylib::RayCollision::RayCollision(const ::Ray& ray, const ::BoundingBox& box) {
    set(::GetRayCollisionBox(ray, box));
}

raylib::RayCollision::RayCollision(
    const ::Ray&    ray,
    const ::Mesh&   mesh,
    const ::Matrix& transform
) {
    set(::GetRayCollisionMesh(ray, mesh, transform));
}

raylib::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    vec1,
    ::Vector3    vec2,
    ::Vector3    vec3,
    ::Vector3    vec4
) {
    set(::GetRayCollisionQuad(ray, vec1, vec2, vec3, vec4));
}

raylib::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    center,
    float        radius
) {
    set(::GetRayCollisionSphere(ray, center, radius));
}

raylib::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    vec1,
    ::Vector3    vec2,
    ::Vector3    vec3
) {
    set(::GetRayCollisionTriangle(ray, vec1, vec2, vec3));
}

raylib::RayCollision& raylib::RayCollision::operator=(const ::RayCollision& ray
) {
    set(ray);
    return *this;
}

void raylib::RayCollision::set(const ::RayCollision& ray) {
    hit      = ray.hit;
    distance = ray.distance;
    point    = ray.point;
    normal   = ray.normal;
}

bool raylib::RayCollision::GetHit() const {
    return hit;
}

void raylib::RayCollision::SetHit(bool value) {
    hit = value;
}

float raylib::RayCollision::GetDistance() const {
    return distance;
}

void raylib::RayCollision::SetDistance(float value) {
    distance = value;
}

::Vector3 raylib::RayCollision::GetPosition() const {
    return point;
}

void raylib::RayCollision::SetPosition(::Vector3 value) {
    point = value;
}

::Vector3 raylib::RayCollision::GetNormal() const {
    return normal;
}

void raylib::RayCollision::SetNormal(::Vector3 value) {
    normal = value;
}
