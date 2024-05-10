#pragma once

#include "raylib/raylib.h"
#include "raylib/vector2.h"

namespace raylib {
/**
 * Input-related functions: mouse
 */
namespace Mouse {
/**
 * Detect if a mouse button has been pressed once
 */
[[maybe_unused]]
static inline bool IsButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

/**
 * Detect if a mouse button is being pressed
 */
[[maybe_unused]]
static inline bool IsButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

/**
 * Detect if a mouse button has been released once
 */
[[maybe_unused]]
static inline bool IsButtonReleased(int button) {
    return ::IsMouseButtonReleased(button);
}

[[maybe_unused]]
static inline bool IsButtonUp(int button) {
    return ::IsMouseButtonUp(button);
}

[[maybe_unused]]
static inline int GetX() {
    return ::GetMouseX();
}

[[maybe_unused]]
static inline int GetY() {
    return ::GetMouseY();
}

[[maybe_unused]]
static inline void SetX(int x) {
    ::SetMousePosition(x, GetY());
}

[[maybe_unused]]
static inline void SetY(int y) {
    ::SetMousePosition(GetX(), y);
}

[[maybe_unused]]
static inline Vector2 GetPosition() {
    return ::GetMousePosition();
}

[[maybe_unused]]
static inline void SetPosition(int x, int y) {
    ::SetMousePosition(x, y);
}

[[maybe_unused]]
static inline void SetPosition(::Vector2 position) {
    ::SetMousePosition(
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

/**
 * Get mouse delta between frames
 */
[[maybe_unused]]
static inline Vector2 GetDelta() {
    return ::GetMouseDelta();
}

[[maybe_unused]]
static inline void SetOffset(int offsetX = 0, int offsetY = 0) {
    ::SetMouseOffset(offsetX, offsetY);
}

[[maybe_unused]]
static inline void SetOffset(::Vector2 offset) {
    ::SetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
}

[[maybe_unused]]
static inline void SetScale(float scaleX = 1.0f, float scaleY = 1.0f) {
    ::SetMouseScale(scaleX, scaleY);
}

[[maybe_unused]]
static inline void SetScale(::Vector2 scale) {
    ::SetMouseScale(scale.x, scale.y);
}

/**
 * Get mouse wheel movement for X or Y, whichever is larger
 */
[[maybe_unused]]
static inline float GetWheelMove() {
    return ::GetMouseWheelMove();
}

/**
 * Get mouse wheel movement for both X and Y
 *
 * @see ::GetMouseWheelMoveV()
 */
[[maybe_unused]]
static inline Vector2 GetWheelMoveV() {
    return GetMouseWheelMoveV();
}

/**
 * Sets the current mouse cursor icon.
 *
 * @see ::MouseCursor
 */
[[maybe_unused]]
static inline void SetCursor(int cursor = MOUSE_CURSOR_DEFAULT) {
    ::SetMouseCursor(cursor);
}

/**
 * Get touch position X for touch point 0 (relative to screen size)
 */
[[maybe_unused]]
static inline int GetTouchX() {
    return ::GetTouchX();
}

/**
 * Get touch position Y for touch point 0 (relative to screen size)
 */
[[maybe_unused]]
static inline int GetTouchY() {
    return ::GetTouchY();
}

/**
 * Get touch position XY for a touch point index (relative to screen size)
 */
[[maybe_unused]]
static inline Vector2 GetTouchPosition(int index) {
    return ::GetTouchPosition(index);
}

/**
 * Get a ray trace from mouse position
 */
[[maybe_unused]]
static inline Ray GetRay(::Vector2 mousePosition, const ::Camera& camera) {
    return ::GetMouseRay(mousePosition, camera);
}

/**
 * Get a ray trace from mouse position
 */
[[maybe_unused]]
static inline Ray GetRay(const ::Camera& camera) {
    return ::GetMouseRay(::GetMousePosition(), camera);
}
}; // namespace Mouse
} // namespace raylib
