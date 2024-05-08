#include "raylib/camera3d.h"

void raylib::Camera3D::set(const ::Camera3D& camera) {
    position   = camera.position;
    target     = camera.target;
    up         = camera.up;
    fovy       = camera.fovy;
    projection = camera.projection;
}

raylib::Camera3D::Camera3D(const ::Camera3D& camera) {
    set(camera);
}

raylib::Camera3D::Camera3D(
    ::Vector3 _position,
    ::Vector3 _target,
    ::Vector3 _up,
    float     _fovy,
    int       _projection
)
    : ::Camera3D{_position, _target, _up, _fovy, _projection} {}

raylib::Camera3D::Camera3D() {}

::Vector3 raylib::Camera3D::GetPosition() const {
    return position;
}

void raylib::Camera3D::SetPosition(::Vector3 value) {
    position = value;
}

::Vector3 raylib::Camera3D::GetTarget() const {
    return target;
}

void raylib::Camera3D::SetTarget(::Vector3 value) {
    target = value;
}

::Vector3 raylib::Camera3D::GetUp() const {
    return up;
}

void raylib::Camera3D::SetUp(::Vector3 value) {
    up = value;
}

float raylib::Camera3D::GetFovy() const {
    return fovy;
}

void raylib::Camera3D::SetFovy(float value) {
    fovy = value;
}

int raylib::Camera3D::GetProjection() const {
    return projection;
}

void raylib::Camera3D::SetProjection(int value) {
    projection = value;
}

raylib::Camera3D& raylib::Camera3D::operator=(const ::Camera3D& camera) {
    set(camera);
    return *this;
}

raylib::Camera3D& raylib::Camera3D::BeginMode() {
    ::BeginMode3D(*this);
    return *this;
}

raylib::Camera3D& raylib::Camera3D::EndMode() {
    ::EndMode3D();
    return *this;
}

Matrix raylib::Camera3D::GetMatrix() const {
    return ::GetCameraMatrix(*this);
}

raylib::Camera3D& raylib::Camera3D::Update(int mode) {
    ::UpdateCamera(this, mode);
    return *this;
}

raylib::Camera3D&
raylib::Camera3D::Update(::Vector3 movement, ::Vector3 rotation, float zoom) {
    ::UpdateCameraPro(this, movement, rotation, zoom);
    return *this;
}

Ray raylib::Camera3D::GetMouseRay(::Vector2 mousePosition) const {
    return ::GetMouseRay(mousePosition, *this);
}

Vector2 raylib::Camera3D::GetWorldToScreen(::Vector3 _position) const {
    return ::GetWorldToScreen(_position, *this);
}

void raylib::Camera3D::DrawBillboard(
    const ::Texture2D& texture,
    ::Vector3          center,
    float              size,
    ::Color            tint
) const {
    ::DrawBillboard(*this, texture, center, size, tint);
}

void raylib::Camera3D::DrawBillboard(
    const ::Texture2D& texture,
    ::Rectangle        sourceRec,
    ::Vector3          center,
    ::Vector2          size,
    ::Color            tint
) const {
    ::DrawBillboardRec(*this, texture, sourceRec, center, size, tint);
}
