#pragma once

#include "core/raycpp/raylib.h"

namespace core::raycpp {
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
static inline int GetKeyPressed() {
    return ::GetKeyPressed();
}

[[maybe_unused]]
static inline int GetCharPressed() {
    return ::GetCharPressed();
}
}; // namespace Keyboard
} // namespace core::raycpp
