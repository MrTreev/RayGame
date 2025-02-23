#pragma once
#include "raygame/core/window/detail/backends.h" // IWYU pragma: keep
#include "raygame/core/window/window.h"

namespace core::window::detail {
class CocoaWindowImpl final: public WindowImpl {
    consteval bool enabled() { return config::EnabledBackends::cocoa(); }

public:
    explicit CocoaWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    CocoaWindowImpl(const CocoaWindowImpl&)           = delete;
    CocoaWindowImpl operator=(const CocoaWindowImpl&) = delete;
    CocoaWindowImpl(CocoaWindowImpl&&)                = default;
    CocoaWindowImpl& operator=(CocoaWindowImpl&&)     = default;
    ~CocoaWindowImpl() final;

    void draw(const drawing::ImageView& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
#if defined(RAYGAME_GUI_BACKEND_COCOA)
#endif
};
} // namespace core::window::detail
