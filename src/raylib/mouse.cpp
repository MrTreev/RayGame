#include "raylib/mouse.h"

bool raylib::Mouse::IsButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

bool raylib::Mouse::IsButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

bool raylib::Mouse::IsButtonReleased(int button) {
    return ::IsMouseButtonReleased(button);
}

bool raylib::Mouse::IsButtonUp(int button) {
    return ::IsMouseButtonUp(button);
}

int raylib::Mouse::GetX() {
    return ::GetMouseX();
}

int raylib::Mouse::GetY() {
    return ::GetMouseY();
}

void raylib::Mouse::SetX(int xpos) {
    ::SetMousePosition(xpos, GetY());
}

void raylib::Mouse::SetY(int ypos) {
    ::SetMousePosition(GetX(), ypos);
}

raylib::Vector2 raylib::Mouse::GetPosition() {
    return Vector2(::GetMousePosition());
}

void raylib::Mouse::SetPosition(int xpos, int ypos) {
    ::SetMousePosition(xpos, ypos);
}

void raylib::Mouse::SetPosition(::Vector2 position) {
    ::SetMousePosition(
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

raylib::Vector2 raylib::Mouse::GetDelta() {
    return Vector2(::GetMouseDelta());
}

void raylib::Mouse::SetOffset(int offsetX, int offsetY) {
    ::SetMouseOffset(offsetX, offsetY);
}

void raylib::Mouse::SetOffset(::Vector2 offset) {
    ::SetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
}

void raylib::Mouse::SetScale(float scaleX, float scaleY) {
    ::SetMouseScale(scaleX, scaleY);
}

void raylib::Mouse::SetScale(::Vector2 scale) {
    ::SetMouseScale(scale.x, scale.y);
}

float raylib::Mouse::GetWheelMove() {
    return ::GetMouseWheelMove();
}

raylib::Vector2 raylib::Mouse::GetWheelMoveV() {
    return Vector2(GetMouseWheelMoveV());
}

void raylib::Mouse::SetCursor(int cursor) {
    ::SetMouseCursor(cursor);
}

int raylib::Mouse::GetTouchX() {
    return ::GetTouchX();
}

int raylib::Mouse::GetTouchY() {
    return ::GetTouchY();
}

raylib::Vector2 raylib::Mouse::GetTouchPosition(int index) {
    return Vector2(::GetTouchPosition(index));
}

Ray
raylib::Mouse::GetRay(::Vector2 mousePosition, const ::Camera& camera) {
    return ::GetMouseRay(mousePosition, camera);
}

Ray raylib::Mouse::GetRay(const ::Camera& camera) {
    return ::GetMouseRay(::GetMousePosition(), camera);
}
