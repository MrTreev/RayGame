#pragma once

#include "raylib/raylib.h"

namespace raylib {
namespace Keyboard {
[[maybe_unused]]
static inline bool IsKeyPressed(int key) {
    return ::IsKeyPressed(key);
}

[[maybe_unused]]
static inline bool IsKeyPressedRepeat(int key) {
    return ::IsKeyPressedRepeat(key);
}

[[maybe_unused]]
static inline bool IsKeyDown(int key) {
    return ::IsKeyDown(key);
}

[[maybe_unused]]
static inline bool IsKeyReleased(int key) {
    return ::IsKeyReleased(key);
}

[[maybe_unused]]
static inline bool IsKeyUp(int key) {
    return ::IsKeyUp(key);
}

[[maybe_unused]]
static inline bool GetKeyPressed() {
    return ::GetKeyPressed() != 0;
}

[[maybe_unused]]
static inline bool GetCharPressed() {
    return ::GetCharPressed() != 0;
}
}; // namespace Keyboard
} // namespace raylib
