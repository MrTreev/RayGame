#pragma once
#include "raygame/core/application/application.h"

namespace core::detail {
class CocoaWindowImpl final: public AppImpl {
public:
    CocoaWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style);
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
} // namespace core::detail
