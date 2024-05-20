#include "core/raycpp/mouse.h"

bool core::raycpp::Mouse::IsButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

bool core::raycpp::Mouse::IsButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

bool core::raycpp::Mouse::IsButtonReleased(int button) {
    return ::IsMouseButtonReleased(button);
}

bool core::raycpp::Mouse::IsButtonUp(int button) {
    return ::IsMouseButtonUp(button);
}

int core::raycpp::Mouse::GetX() {
    return ::GetMouseX();
}

int core::raycpp::Mouse::GetY() {
    return ::GetMouseY();
}

void core::raycpp::Mouse::SetX(int xpos) {
    ::SetMousePosition(xpos, GetY());
}

void core::raycpp::Mouse::SetY(int ypos) {
    ::SetMousePosition(GetX(), ypos);
}

core::raycpp::Vector2 core::raycpp::Mouse::GetPosition() {
    return Vector2(::GetMousePosition());
}

void core::raycpp::Mouse::SetPosition(int xpos, int ypos) {
    ::SetMousePosition(xpos, ypos);
}

void core::raycpp::Mouse::SetPosition(::Vector2 position) {
    ::SetMousePosition(
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

core::raycpp::Vector2 core::raycpp::Mouse::GetDelta() {
    return Vector2(::GetMouseDelta());
}

void core::raycpp::Mouse::SetOffset(int offsetX, int offsetY) {
    ::SetMouseOffset(offsetX, offsetY);
}

void core::raycpp::Mouse::SetOffset(::Vector2 offset) {
    ::SetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
}

void core::raycpp::Mouse::SetScale(float scaleX, float scaleY) {
    ::SetMouseScale(scaleX, scaleY);
}

void core::raycpp::Mouse::SetScale(::Vector2 scale) {
    ::SetMouseScale(scale.x, scale.y);
}

float core::raycpp::Mouse::GetWheelMove() {
    return ::GetMouseWheelMove();
}

core::raycpp::Vector2 core::raycpp::Mouse::GetWheelMoveV() {
    return Vector2(GetMouseWheelMoveV());
}

void core::raycpp::Mouse::SetCursor(int cursor) {
    ::SetMouseCursor(cursor);
}

int core::raycpp::Mouse::GetTouchX() {
    return ::GetTouchX();
}

int core::raycpp::Mouse::GetTouchY() {
    return ::GetTouchY();
}

core::raycpp::Vector2 core::raycpp::Mouse::GetTouchPosition(int index) {
    return Vector2(::GetTouchPosition(index));
}

Ray
core::raycpp::Mouse::GetRay(::Vector2 mousePosition, const ::Camera& camera) {
    return ::GetMouseRay(mousePosition, camera);
}

Ray core::raycpp::Mouse::GetRay(const ::Camera& camera) {
    return ::GetMouseRay(::GetMousePosition(), camera);
}
