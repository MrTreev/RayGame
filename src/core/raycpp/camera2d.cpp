#include "core/raycpp/camera2d.h"

void core::raycpp::Camera2D::set(const ::Camera2D& camera) {
    offset   = camera.offset;
    target   = camera.target;
    rotation = camera.rotation;
    zoom     = camera.zoom;
}

core::raycpp::Camera2D::Camera2D(const ::Camera2D& camera) {
    set(camera);
}

core::raycpp::Camera2D::Camera2D() {}

core::raycpp::Camera2D::Camera2D(
    ::Vector2 _offset,
    ::Vector2 _target,
    float     _rotation,
    float     _zoom
)
    : ::Camera2D{_offset, _target, _rotation, _zoom} {}

void core::raycpp::Camera2D::BeginMode() {
    ::BeginMode2D(*this);
}

void core::raycpp::Camera2D::EndMode() {
    ::EndMode2D();
}

::Vector2 core::raycpp::Camera2D::GetOffset() const {
    return offset;
}

void core::raycpp::Camera2D::SetOffset(::Vector2 value) {
    offset = value;
}

::Vector2 core::raycpp::Camera2D::GetTarget() const {
    return target;
}

void core::raycpp::Camera2D::SetTarget(::Vector2 value) {
    target = value;
}

float core::raycpp::Camera2D::GetRotation() const {
    return rotation;
}

void core::raycpp::Camera2D::SetRotation(float value) {
    rotation = value;
}

float core::raycpp::Camera2D::GetZoom() const {
    return zoom;
}

void core::raycpp::Camera2D::SetZoom(float value) {
    zoom = value;
}

core::raycpp::Camera2D& core::raycpp::Camera2D::operator=(const ::Camera2D& camera) {
    set(camera);
    return *this;
}

Matrix core::raycpp::Camera2D::GetMatrix() const {
    return ::GetCameraMatrix2D(*this);
}

core::raycpp::Vector2 core::raycpp::Camera2D::GetScreenToWorld(::Vector2 position) const {
    return core::raycpp::Vector2(::GetScreenToWorld2D(position, *this));
}

core::raycpp::Vector2 core::raycpp::Camera2D::GetWorldToScreen(::Vector2 position) const {
    return core::raycpp::Vector2(::GetWorldToScreen2D(position, *this));
}
