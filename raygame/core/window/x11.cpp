#include "raygame/core/window/window.h" // IWYU pragma: keep
#if defined(RAYGAME_GUI_BACKEND_X11)
RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#    include <X11/Xlib.h>
RAYGAME_CLANG_SUPPRESS_WARNING_POP
#    include "raygame/core/condition.h"

class core::window::Window::Impl {
    using X_Display = ::Display;
    using X_XEvent  = ::XEvent;
    using X_Window  = ::Window;
    bool         m_should_close{false};
    Vec2<size_t> m_size{DEFAULT_WINDOW_SIZE};
    std::string  m_title{DEFAULT_WINDOW_TITLE};
    WindowStyle  m_style{DEFAULT_WINDOW_STYLE};
    X_Display*   m_display{nullptr};
    int          m_screen{0};
    X_XEvent     m_event{};
    X_Window     m_window{};

public:
    explicit Impl(Vec2<size_t> size, std::string title, WindowStyle style);
    ~Impl();
    Impl(const Impl&)            = delete;
    Impl& operator=(const Impl&) = delete;
    Impl(Impl&&)                 = default;
    Impl& operator=(Impl&&)      = default;

    void new_buffer(core::Vec2<size_t> size);
    void render_frame();
    void set_style(WindowStyle style);
    [[nodiscard]]
    const size_t& buf_width() const;
    [[nodiscard]]
    const size_t& buf_height() const;

    [[nodiscard]]
    bool should_close() const {
        return m_should_close;
    }
};

core::window::Window::Impl::Impl(
    Vec2<size_t> size,
    std::string  title,
    WindowStyle  style
)
    : m_size(size)
    , m_title(std::move(title))
    , m_style(style)
    , m_display(XOpenDisplay(nullptr))
    , m_screen(DefaultScreen(m_display))
    , m_window(XCreateSimpleWindow(
          m_display,
          RootWindow(m_display, m_screen),
          0,
          0,
          math::numeric_cast<uint32_t>(buf_width()),
          math::numeric_cast<uint32_t>(buf_height()),
          1U,
          WhitePixel(m_display, m_screen),
          BlackPixel(m_display, m_screen)
      )) {
    core::condition::check_ptr(m_display, "Could not open Display");
    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
    XMapWindow(m_display, m_window);
}

core::window::Window::Impl::~Impl() {
    XCloseDisplay(m_display);
}

void core::window::Window::Impl::render_frame() {
    XNextEvent(m_display, &m_event);
    if (m_event.type == Expose) {
        // Draw stuff here
    }
    if (m_event.type == KeyPress) {
        m_should_close = true;
    }
}

void core::window::Window::draw(const drawing::Image& image) {
    std::ignore = image;
}
#endif
