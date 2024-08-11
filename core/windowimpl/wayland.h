#pragma once
#include "core/window.h"
#include "core/windowimpl/wayland/pixelbuffer.h"
#include "core/windowimpl/wayland/region.h"
#include "core/windowimpl/wayland/surface.h"
#include "core/windowimpl/wayland/window.h"

namespace core::window::wayland {

//! Create a pixel buffer for wayland
/*!
 *  @param width         Width of the desired pixel buffer
 *  @param width         Height of the desired pixel buffer
 *  @param buffer_size   Size of the desired pixel buffer
 */
struct wl_buffer* create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
);

/*!
 *  @overload
 *  @param width Width of the desired pixel buffer
 *  @param width Height of the desired pixel buffer
 */
struct wl_buffer* create_buffer(const size_t& width, const size_t& height);

//! Initialise a Wayland window
/*!
 *  @param width        Width of the window and initial window buffer
 *  @param height       Height of the window and initial window buffer
 *  @param buffer_size  Size of the initial window buffer
 *  @param title       	Title of the wayland window
 *  @param style        Style the window will request from the compositor
 */
void init_window(
    const size_t&            width,
    const size_t&            height,
    const size_t&            buffer_size,
    const std::string&       title,
    const core::WindowStyle& style
);

//! Destroy a Wayland window
void destroy_window();

void render_frame(const size_t& width, const size_t& height);

bool should_close();

} // namespace core::window::wayland
