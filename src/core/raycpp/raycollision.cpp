#include "core/raycpp/raycollision.h"

core::raycpp::RayCollision::RayCollision(const ::RayCollision& ray) {
    set(ray);
}

core::raycpp::RayCollision::RayCollision(
    bool      _hit,
    float     _distance,
    ::Vector3 _point,
    ::Vector3 _normal
)
    : ::RayCollision{_hit, _distance, _point, _normal} {
    // Nothing.
}

core::raycpp::RayCollision::RayCollision(const ::Ray& ray, const ::BoundingBox& box) {
    set(::GetRayCollisionBox(ray, box));
}

core::raycpp::RayCollision::RayCollision(
    const ::Ray&    ray,
    const ::Mesh&   mesh,
    const ::Matrix& transform
) {
    set(::GetRayCollisionMesh(ray, mesh, transform));
}

core::raycpp::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    vec1,
    ::Vector3    vec2,
    ::Vector3    vec3,
    ::Vector3    vec4
) {
    set(::GetRayCollisionQuad(ray, vec1, vec2, vec3, vec4));
}

core::raycpp::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    center,
    float        radius
) {
    set(::GetRayCollisionSphere(ray, center, radius));
}

core::raycpp::RayCollision::RayCollision(
    const ::Ray& ray,
    ::Vector3    vec1,
    ::Vector3    vec2,
    ::Vector3    vec3
) {
    set(::GetRayCollisionTriangle(ray, vec1, vec2, vec3));
}

core::raycpp::RayCollision& core::raycpp::RayCollision::operator=(const ::RayCollision& ray
) {
    set(ray);
    return *this;
}

void core::raycpp::RayCollision::set(const ::RayCollision& ray) {
    hit      = ray.hit;
    distance = ray.distance;
    point    = ray.point;
    normal   = ray.normal;
}

bool core::raycpp::RayCollision::GetHit() const {
    return hit;
}

void core::raycpp::RayCollision::SetHit(bool value) {
    hit = value;
}

float core::raycpp::RayCollision::GetDistance() const {
    return distance;
}

void core::raycpp::RayCollision::SetDistance(float value) {
    distance = value;
}

::Vector3 core::raycpp::RayCollision::GetPosition() const {
    return point;
}

void core::raycpp::RayCollision::SetPosition(::Vector3 value) {
    point = value;
}

::Vector3 core::raycpp::RayCollision::GetNormal() const {
    return normal;
}

void core::raycpp::RayCollision::SetNormal(::Vector3 value) {
    normal = value;
}
