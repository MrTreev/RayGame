#pragma once
#include "raygame/core/window/window.h"

namespace core::window::detail {
class CocoaWindowImpl final: public WindowImpl {
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

    void draw(const drawing::Image& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;
};
} // namespace core::window::detail
