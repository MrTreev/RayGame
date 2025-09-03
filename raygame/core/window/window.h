#pragma once
#include "raygame/core/config.h"
#include "raygame/core/drawing/image.h"
#include "raygame/core/math/ring_average.h"
#include "raygame/core/math/timer.h"
#include <chrono>
#include <string>

namespace core::window {
//! Default Window Width
static constexpr std::size_t DEFAULT_WINDOW_WIDTH  = RAYGAME_DEFAULT_WINDOW_WIDTH;
//! Default Window Height
static constexpr std::size_t DEFAULT_WINDOW_HEIGHT = RAYGAME_DEFAULT_WINDOW_HEIGHT;
//! Default Window Title
static constexpr std::string DEFAULT_WINDOW_TITLE  = RAYGAME_DEFAULT_WINDOW_TITLE;

//! Window display styles
enum class WindowStyle : uint8_t {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr WindowStyle DEFAULT_WINDOW_STYLE = WindowStyle::Windowed;

static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};

class Window {
    class WindowData;

    class WindowDeleter {
    public:
        void operator()(WindowData*);
    };

    std::unique_ptr<WindowData, WindowDeleter> m_data;

    Vec2<size_t> m_size;
    std::string  m_title;
    WindowStyle  m_style;

    math::HighResolutionTimer                      m_timer;
    math::RingAverage<int64_t, config::TARGET_FPS> m_counter;

    void set_size(Vec2<size_t> size);
    void set_title(std::string title);
    void set_style(WindowStyle style);

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
    ~Window();

    [[nodiscard]] const Vec2<size_t>& get_size() const { return m_size; }
    [[nodiscard]] const std::string& get_title() const { return m_title; }
    [[nodiscard]] const WindowStyle& get_style() const { return m_style; }
    [[nodiscard]] int64_t frame_time() { return m_counter.average(); }
    void frame_time_start() { m_timer.start(); }
    void frame_time_end() { m_timer.end(); m_counter.add(m_timer.ms().count()); }

    std::string frame_stats();

    void draw(const drawing::ImageView& image);

    void restyle(WindowStyle style);

    void render_frame();

    [[nodiscard]]
    bool next_frame();
    [[nodiscard]]
    bool should_close() const;

    [[nodiscard]]
    const size_t& width() const {
        return m_size.x;
    }

    [[nodiscard]]
    const size_t& height() const {
        return m_size.y;
    }
};

} // namespace core::window
