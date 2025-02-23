#pragma once
#include "raygame/core/window/detail/backends.h" // IWYU pragma: keep
#include "raygame/core/window/window.h"

namespace core::window::detail {
class DwmWindowImpl final: public WindowImpl {
    consteval bool enabled() { return config::EnabledBackends::dwm(); }

public:
    explicit DwmWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    DwmWindowImpl(const DwmWindowImpl&)           = delete;
    DwmWindowImpl operator=(const DwmWindowImpl&) = delete;
    DwmWindowImpl(DwmWindowImpl&&)                = default;
    DwmWindowImpl& operator=(DwmWindowImpl&&)     = default;
    ~DwmWindowImpl() final;

    void draw(const drawing::ImageView& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
#if defined(RAYGAME_GUI_BACKEND_DWM)
#endif
};
} // namespace core::window::detail
