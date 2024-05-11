#include "raylib/camera2d.h"

void raylib::Camera2D::set(const ::Camera2D& camera) {
    offset   = camera.offset;
    target   = camera.target;
    rotation = camera.rotation;
    zoom     = camera.zoom;
}

raylib::Camera2D::Camera2D(const ::Camera2D& camera) {
    set(camera);
}

raylib::Camera2D::Camera2D() {}

raylib::Camera2D::Camera2D(
    ::Vector2 _offset,
    ::Vector2 _target,
    float     _rotation,
    float     _zoom
)
    : ::Camera2D{_offset, _target, _rotation, _zoom} {}

void raylib::Camera2D::BeginMode() {
    ::BeginMode2D(*this);
}

void raylib::Camera2D::EndMode() {
    ::EndMode2D();
}

::Vector2 raylib::Camera2D::GetOffset() const {
    return offset;
}

void raylib::Camera2D::SetOffset(::Vector2 value) {
    offset = value;
}

::Vector2 raylib::Camera2D::GetTarget() const {
    return target;
}

void raylib::Camera2D::SetTarget(::Vector2 value) {
    target = value;
}

float raylib::Camera2D::GetRotation() const {
    return rotation;
}

void raylib::Camera2D::SetRotation(float value) {
    rotation = value;
}

float raylib::Camera2D::GetZoom() const {
    return zoom;
}

void raylib::Camera2D::SetZoom(float value) {
    zoom = value;
}

raylib::Camera2D& raylib::Camera2D::operator=(const ::Camera2D& camera) {
    set(camera);
    return *this;
}

Matrix raylib::Camera2D::GetMatrix() const {
    return ::GetCameraMatrix2D(*this);
}

raylib::Vector2 raylib::Camera2D::GetScreenToWorld(::Vector2 position) const {
    return raylib::Vector2(::GetScreenToWorld2D(position, *this));
}

raylib::Vector2 raylib::Camera2D::GetWorldToScreen(::Vector2 position) const {
    return raylib::Vector2(::GetWorldToScreen2D(position, *this));
}
