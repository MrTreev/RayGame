#pragma once
#include "gui/vector.h"

namespace gui {

class Rect {
private:
    ::Rectangle _rectangle;

public:
    Rect(
        const float& xpos,
        const float& ypos,
        const float& width,
        const float& height
    )
        : _rectangle({xpos, ypos, width, height}){};
    Rect(const Vec2d& position, const Vec2d& size)
        : _rectangle({position.x(), position.y(), size.x(), size.y()}){};
};

} // namespace gui
