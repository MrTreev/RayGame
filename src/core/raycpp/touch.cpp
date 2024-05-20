#include "core/raycpp/touch.h"

int core::raycpp::Touch::GetX() {
    return ::GetTouchX();
}

int core::raycpp::Touch::GetY() {
    return ::GetTouchY();
}

Vector2 core::raycpp::Touch::GetPosition(int index) {
    return ::GetTouchPosition(index);
}

int core::raycpp::Touch::GetPointId(int index) {
    return ::GetTouchPointId(index);
}

int core::raycpp::Touch::GetPointCount() {
    return ::GetTouchPointCount();
}
