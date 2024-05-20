#pragma once

#include "core/raycpp/raylib.h"

namespace core::raycpp {
namespace Touch {
[[maybe_unused]]
static int GetX();

[[maybe_unused]]
static int GetY();

[[maybe_unused]]
static Vector2 GetPosition(int index);

[[maybe_unused]]
static int GetPointId(int index);

[[maybe_unused]]
static int GetPointCount();

}; // namespace Touch
} // namespace core::raycpp
