#pragma once
#include "raygame/core/window/input.h"
#include "raygame/core/window/window.h"

namespace core {
class Application {
protected:
    window::Window      m_window;
    window::InputMapper m_inputmapper;

public:
    explicit Application(
        Vec2<size_t>        size  = window::DEFAULT_WINDOW_SIZE,
        std::string         title = window::DEFAULT_WINDOW_TITLE,
        window::WindowStyle style = window::DEFAULT_WINDOW_STYLE
    );
};
} // namespace core
