#pragma once
#include "raygame/core/config.h"
#include "raygame/core/drawing/image.h"
#include <string>
#include <utility>

namespace core::window {
//! Default Window Width
static constexpr std::size_t DEFAULT_WINDOW_WIDTH =
    RAYGAME_DEFAULT_WINDOW_WIDTH;
//! Default Window Height
static constexpr std::size_t DEFAULT_WINDOW_HEIGHT =
    RAYGAME_DEFAULT_WINDOW_HEIGHT;
//! Default Window Title
static constexpr std::string DEFAULT_WINDOW_TITLE =
    RAYGAME_DEFAULT_WINDOW_TITLE;

//! Window display styles
enum class WindowStyle : uint8_t {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr WindowStyle DEFAULT_WINDOW_STYLE = WindowStyle::Windowed;

static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

namespace detail {
class WindowImpl {
    Vec2<size_t> m_size;
    std::string  m_title;
    WindowStyle  m_style;

protected:
    void set_size(Vec2<size_t> size) { m_size = size; }

    void set_title(std::string title) { m_title = std::move(title); }

    void set_style(WindowStyle style) { m_style = style; }

    [[nodiscard]]
    const Vec2<size_t>& get_size() const {
        return m_size;
    }

    [[nodiscard]]
    const std::string& get_title() const {
        return m_title;
    }

    [[nodiscard]]
    const WindowStyle& get_style() const {
        return m_style;
    }

public:
    //! Constructs a window
    explicit WindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    )
        : m_size(size)
        , m_title(std::move(title))
        , m_style(style) {}

    WindowImpl(const WindowImpl&)           = delete;
    WindowImpl operator=(const WindowImpl&) = delete;
    WindowImpl(WindowImpl&&)                = default;
    WindowImpl& operator=(WindowImpl&&)     = default;
    virtual ~WindowImpl();

    virtual void draw(const drawing::ImageView& image);

    virtual void restyle(WindowStyle style);

    virtual void render_frame();

    [[nodiscard]]
    virtual bool next_frame();

    [[nodiscard]]
    virtual bool should_close() const;

    [[nodiscard]]
    const size_t& width() const {
        return m_size.x;
    }

    [[nodiscard]]
    const size_t& height() const {
        return m_size.y;
    }
};
} // namespace detail

class Window {
    std::unique_ptr<detail::WindowImpl> m_impl;

public:
    //! Constructs a window
    explicit Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );

    Window(const Window&)           = delete;
    Window operator=(const Window&) = delete;
    Window(Window&&)                = default;
    Window& operator=(Window&&)     = default;
    ~Window()                       = default;

    void draw(const drawing::ImageView& image) { m_impl->draw(image); }

    void restyle(WindowStyle style) { m_impl->restyle(style); }

    void render_frame() { m_impl->render_frame(); }

    [[nodiscard]]
    bool next_frame() {
        return m_impl->next_frame();
    }

    [[nodiscard]]
    bool should_close() const {
        return m_impl->should_close();
    }

    [[nodiscard]]
    const size_t& width() const {
        return m_impl->width();
    }

    [[nodiscard]]
    const size_t& height() const {
        return m_impl->height();
    }
};

} // namespace core::window
