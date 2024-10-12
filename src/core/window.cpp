#include "core/window.h" // IWYU pragma: keep

core::Window::Window(Vec2<size_t> size, std::string title, WindowStyle style)
    : m_size(std::move(size))
    , m_title(std::move(title))
    , m_style(std::move(style)) {}

core::Window::~Window() = default;
