#pragma once
#include "raygame/core/window/window.h"

namespace core::window::detail {
class TempleWindowImpl final: public WindowImpl {
public:
    explicit TempleWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    TempleWindowImpl(const TempleWindowImpl&)           = delete;
    TempleWindowImpl operator=(const TempleWindowImpl&) = delete;
    TempleWindowImpl(TempleWindowImpl&&)                = default;
    TempleWindowImpl& operator=(TempleWindowImpl&&)     = default;
    ~TempleWindowImpl() final;

    void draw(const drawing::Image& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;
};
} // namespace core::window::detail
