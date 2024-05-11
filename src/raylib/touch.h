#pragma once

#include "raylib/raylib.h"

namespace raylib {
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
} // namespace raylib
