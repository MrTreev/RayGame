#pragma once
#include "raygame/core/application/application.h"

namespace core::detail {
class DwmWindowImpl final: public AppImpl {
public:
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
} // namespace core::detail
