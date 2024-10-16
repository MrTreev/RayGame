#pragma once
#include "core/window.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#include <X11/Xlib.h>
#pragma clang diagnostic pop

namespace core::window {

class X11Window: public Window<X11Window> {
    using XWindow = ::Window;

public:
    X11Window(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ~X11Window();
    void set_style(WindowStyle style);
    bool next_frame();

    bool should_close();

private:
    Display* m_display = nullptr;
    int      m_screen  = 0;
    XWindow  m_window;
    XEvent   m_event;
};

} // namespace core::window
