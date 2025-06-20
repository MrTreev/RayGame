#pragma once
#include "raygame/core/window/detail/backends.h"
#include "raygame/core/window/window.h"

namespace core::window::detail {
class DwmWindowImpl final: public WindowImpl {
public:
    RAYGAME_RETURN_DWM
    DwmWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style);
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
};
} // namespace core::window::detail
