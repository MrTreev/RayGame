#pragma once
#include "gui/vector.h"
#include "gui/raylib_include.h"

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
        : _rectangle({xpos, ypos, width, height}) {}

    Rect(const gui::Vec2d& position, const gui::Vec2d& size)
        : _rectangle({position.x(), position.y(), size.x(), size.y()}) {}

    [[nodiscard]]
    ::Rectangle rect() const {
        return _rectangle;
    }

    [[nodiscard]]
    float x() const {
        return _rectangle.x;
    }

    [[nodiscard]]
    float y() const {
        return _rectangle.y;
    }

    [[nodiscard]]
    float width() const {
        return _rectangle.width;
    }

    [[nodiscard]]
    float height() const {
        return _rectangle.height;
    }
};

} // namespace gui
