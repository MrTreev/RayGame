#pragma once
#include "raygame/core/window/input.h"
#include "raygame/core/window/window.h"

namespace core {
class Application {
    window::Window      m_window;
    window::InputMapper m_inputmapper;

public:
    explicit Application(
        Vec2<size_t>        size  = window::DEFAULT_WINDOW_SIZE,
        std::string         title = window::DEFAULT_WINDOW_TITLE,
        window::WindowStyle style = window::DEFAULT_WINDOW_STYLE
    )
        : m_window(size, std::move(title), style) {
        m_inputmapper.set();
    }

    constexpr void draw(const drawing::ImageView& image) { m_window.draw(image); }

    constexpr void restyle(core::window::WindowStyle style) { m_window.restyle(style); }

    constexpr void render_frame() { m_window.render_frame(); }

    [[nodiscard]]
    constexpr bool next_frame() {
        return m_window.next_frame();
    }

    [[nodiscard]]
    constexpr bool should_close() const {
        return m_window.should_close();
    }

    [[nodiscard]]
    constexpr const size_t& width() const {
        return m_window.width();
    }

    [[nodiscard]]
    constexpr const size_t& height() const {
        return m_window.height();
    }
};
} // namespace core
