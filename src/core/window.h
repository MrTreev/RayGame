#pragma once
#include "core/types.h"
#include <string>

namespace core {

//! Window display styles
enum class WindowStyle {
    Windowed,           //!< Windowed mode (resizable)
    WindowedFullscreen, //!< Windowed mode with no decorations (resizable)
    Fullscreen,         //!< Fullscreen mode
};

static constexpr size_t            DEFAULT_WINDOW_WIDTH  = 640;
static constexpr size_t            DEFAULT_WINDOW_HEIGHT = 480;
static constexpr std::string       DEFAULT_WINDOW_TITLE  = "RayGame";
static constexpr core::WindowStyle DEFAULT_WINDOW_STYLE =
    core::WindowStyle::Windowed;
static constexpr Vec2<size_t> DEFAULT_WINDOW_SIZE = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT
};

template<typename T>
concept IsWindow =
    (!std::is_copy_assignable<T>()) && (!std::is_copy_constructible<T>())
    && requires(T window) { window.should_close(); };

template<typename T>
requires IsWindow<T>
T create_window(
    Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
    std::string  title = DEFAULT_WINDOW_TITLE,
    WindowStyle  style = DEFAULT_WINDOW_STYLE
);

} // namespace core
