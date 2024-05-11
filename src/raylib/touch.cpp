#include "raylib/touch.h"

int raylib::Touch::GetX() {
    return ::GetTouchX();
}

int raylib::Touch::GetY() {
    return ::GetTouchY();
}

Vector2 raylib::Touch::GetPosition(int index) {
    return ::GetTouchPosition(index);
}

int raylib::Touch::GetPointId(int index) {
    return ::GetTouchPointId(index);
}

int raylib::Touch::GetPointCount() {
    return ::GetTouchPointCount();
}
