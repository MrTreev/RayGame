#pragma once
#include "gui/raylib_include.h"

namespace gui {

class Rect {
private:
    ::Rectangle _rectangle;

public:
    Rect()
        : _rectangle(){};
};

} // namespace gui
