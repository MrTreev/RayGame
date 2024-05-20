#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/vector2.h"

namespace core::raycpp {
namespace Mouse {
[[maybe_unused]]
static bool IsButtonPressed(int button);

[[maybe_unused]]
static bool IsButtonDown(int button);

[[maybe_unused]]
static bool IsButtonReleased(int button);

[[maybe_unused]]
static bool IsButtonUp(int button);

[[maybe_unused]]
static int GetX();

[[maybe_unused]]
static int GetY();

[[maybe_unused]]
static void SetX(int xpos);

[[maybe_unused]]
static void SetY(int ypos);

[[maybe_unused]]
static Vector2 GetPosition();

[[maybe_unused]]
static void SetPosition(int xpos, int ypos);

[[maybe_unused]]
static void SetPosition(::Vector2 position);

[[maybe_unused]]
static Vector2 GetDelta();

[[maybe_unused]]
static void SetOffset(int offsetX = 0, int offsetY = 0);

[[maybe_unused]]
static void SetOffset(::Vector2 offset);

[[maybe_unused]]
static void SetScale(float scaleX = 1.0F, float scaleY = 1.0F);

[[maybe_unused]]
static void SetScale(::Vector2 scale);

[[maybe_unused]]
static float GetWheelMove();

[[maybe_unused]]
static Vector2 GetWheelMoveV();

[[maybe_unused]]
static void SetCursor(int cursor = MOUSE_CURSOR_DEFAULT);

[[maybe_unused]]
static int GetTouchX();

[[maybe_unused]]
static int GetTouchY();

[[maybe_unused]]
static Vector2 GetTouchPosition(int index);

[[maybe_unused]]
static Ray GetRay(::Vector2 mousePosition, const ::Camera& camera);

[[maybe_unused]]
static Ray GetRay(const ::Camera& camera);
}; // namespace Mouse
} // namespace core::raycpp
