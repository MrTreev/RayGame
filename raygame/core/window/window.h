#pragma once
#include "raygame/core/config.h"
#include "raygame/core/math/vector.h"
#include <memory>
#include <string>
#include <utility>

namespace core::window {
//! Window display styles
enum class WindowStyle : uint8_t {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};
static constexpr WindowStyle  DEFAULT_WINDOW_STYLE = WindowStyle::Windowed;
static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE  = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

class Window {
private:
    bool         m_should_close = false;
    Vec2<size_t> m_size{DEFAULT_WINDOW_SIZE};
    std::string  m_title{DEFAULT_WINDOW_TITLE};
    [[maybe_unused]]
    WindowStyle m_style{DEFAULT_WINDOW_STYLE};

protected:
    Window(Window&&)            = default;
    Window& operator=(Window&&) = default;

    Window() = default;

    explicit Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    )
        : m_size(size)
        , m_title(std::move(title))
        , m_style(style) {}

    void set_size(Vec2<size_t> size) { m_size = size; }

    Vec2<size_t> win_size() { return m_size; }

    void set_close() { m_should_close = true; }

    void set_title(std::string title) { m_title = std::move(title); }

    const std::string& title() { return m_title; }

    const WindowStyle& style() { return m_style; }

public:
    virtual ~Window();
    Window(const Window&)           = delete;
    Window operator=(const Window&) = delete;

    void set_style(this auto&& self, WindowStyle style) {
        self.m_style = style;
        self.set_style(style);
    }

    virtual void render_frame();

    bool next_frame() {
        if (!should_close()) {
            render_frame();
        }
        return !should_close();
    }

    [[nodiscard]]
    bool should_close() const {
        return m_should_close;
    }
};

std::unique_ptr<Window> dispatch(
    Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
    std::string  title = DEFAULT_WINDOW_TITLE,
    WindowStyle  style = DEFAULT_WINDOW_STYLE
);
} // namespace core::window
