#pragma once
#include "core/types.h"
#include "core/window.h"
#include <memory>
#include <wayland-client-protocol.h>
#include <xdg-shell-client-protocol.h>

namespace core::window::wayland {

class Display {
    static std::unique_ptr<struct wl_display> m_display;

public:
    static void     sync();
    static bool     roundtrip();
    static void     set_user_data(void* user_data);
    static void*    get_user_data();
    static uint32_t get_version();
};

class PixelBuffer {
    size_t m_width;
    size_t m_height;
    size_t m_buffer_size;

public:
    //! Create a pixel buffer for wayland
    /*! 
	 * @param width         Width of the desired pixel buffer
	 * @param width         Height of the desired pixel buffer
	 */
    PixelBuffer(const size_t& width, const size_t& height);
    ~PixelBuffer();

    //! Reallocate the pixel buffer keeping the existing object
    /*! 
	 *
	 * @note does not copy the contents to the new buffer
	 *
	 * @param width         Width of the desired pixel buffer
	 * @param width         Height of the desired pixel buffer
	 */
    void reset(const size_t& width, const size_t& height);

    /*! 
	 * @overload
	 * @param size 	Size of the desired pixel buffer
	 */
    void reset(core::Vec2<size_t> size);
};

class Surface {
    std::unique_ptr<struct wl_surface>  m_wl_surface;
    std::unique_ptr<struct xdg_surface> m_xdg_surface;

public:
    Surface();
    ~Surface();

    //! Damage a region of the surface
    /*!
	 * @param origin 	Origin point of the region to be damaged
	 * @param size 		Size of the region to be damaged
	 */
    void damage(core::Vec2<size_t> origin, core::Vec2<size_t> size);

    //! @overload
    /*!
	 * @param orig_x 	Origin x-point of the region to be damaged
	 * @param orig_y 	Origin y-point of the region to be damaged
	 * @param width 	Width of the region to be damaged
	 * @param height 	Height of the region to be damaged
	 */
    void damage(
        const size_t& orig_x,
        const size_t& orig_y,
        const size_t& width,
        const size_t& height
    );

    //! Attach a pixel buffer to this surface
    void attach(const PixelBuffer& pixbuf);

    //! Commit the surface to the screen
    void commit();
};

//! Create a pixel buffer for wayland
/*! 
 * @param width         Width of the desired pixel buffer
 * @param width         Height of the desired pixel buffer
 * @param buffer_size   Size of the desired pixel buffer
 */
struct wl_buffer* create_buffer(
    const size_t& width,
    const size_t& height,
    const size_t& buffer_size
);
} // namespace core::window::wayland

namespace core::window::wayland {
/*!
 * @overload
 * @param width Width of the desired pixel buffer
 * @param width Height of the desired pixel buffer
 */
struct wl_buffer* create_buffer(const size_t& width, const size_t& height);

//! Initialise a Wayland window
/*!
 * width        Width of the window and initial window buffer
 * height       Height of the window and initial window buffer
 * buffer_size  Size of the initial window buffer
 * title       	Title of the wayland window
 * style        Style the window will request from the compositor
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
