#include <cstring>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xdg-shell-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

class axis_t {
public:
    bool       valid;
    wl_fixed_t value;
    int32_t    discrete;
};

class KeyboardHandler {
    static void enter(
        void*        data,
        wl_keyboard* wl_keyboard,
        uint32_t     serial,
        wl_surface*  surface,
        wl_array*    keys
    );

    static void
    key(void*                         data,
        [[maybe_unused]] wl_keyboard* wl_keyboard,
        [[maybe_unused]] uint32_t     serial,
        [[maybe_unused]] uint32_t     time,
        uint32_t                      key,
        uint32_t                      state);

    static void keymap(
        void*                         data,
        [[maybe_unused]] wl_keyboard* wl_keyboard,
        uint32_t                      format,
        int32_t                       file_desc,
        uint32_t                      size
    );

    static void leave(
        [[maybe_unused]] void*        data,
        [[maybe_unused]] wl_keyboard* wl_keyboard,
        [[maybe_unused]] uint32_t     serial,
        [[maybe_unused]] wl_surface*  surface
    );

    static void modifiers(
        void*                         data,
        [[maybe_unused]] wl_keyboard* wl_keyboard,
        [[maybe_unused]] uint32_t     serial,
        uint32_t                      mods_depressed,
        uint32_t                      mods_latched,
        uint32_t                      mods_locked,
        uint32_t                      group
    );

    static void repeat_info(
        [[maybe_unused]] void*        data,
        [[maybe_unused]] wl_keyboard* wl_keyboard,
        [[maybe_unused]] int32_t      rate,
        [[maybe_unused]] int32_t      delay
    );

public:
    static constexpr const wl_keyboard_listener listener{
        .keymap      = keymap,
        .enter       = enter,
        .leave       = leave,
        .key         = key,
        .modifiers   = modifiers,
        .repeat_info = repeat_info,
    };
};

class PointerHandler {
    static void axis(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     time,
        uint32_t                     axis,
        wl_fixed_t                   value
    );

    static void axis_discrete(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     axis,
        int32_t                      discrete
    );

    static void axis_relative_direction(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        [[maybe_unused]] uint32_t    axis,
        [[maybe_unused]] uint32_t    direction
    );

    static void axis_source(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     axis_source
    );

    static void axis_stop(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     time,
        uint32_t                     axis
    );

    static void axis_value120(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        [[maybe_unused]] uint32_t    axis,
        [[maybe_unused]] int32_t     value120
    );

    static void button(
        void*                        data,
        [[maybe_unused]] wl_pointer* pointer,
        uint32_t                     serial,
        uint32_t                     time,
        uint32_t                     button,
        uint32_t                     state
    );

    static void enter(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     serial,
        [[maybe_unused]] wl_surface* surface,
        wl_fixed_t                   surface_x,
        wl_fixed_t                   surface_y
    );

    static void frame(void* data, [[maybe_unused]] wl_pointer* wl_pointer);

    static void leave(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     serial,
        [[maybe_unused]] wl_surface* surface
    );

    static void motion(
        void*                        data,
        [[maybe_unused]] wl_pointer* wl_pointer,
        uint32_t                     time,
        wl_fixed_t                   surface_x,
        wl_fixed_t                   surface_y
    );

public:
    static constexpr const wl_pointer_listener listener{
        .enter                   = enter,
        .leave                   = leave,
        .motion                  = motion,
        .button                  = button,
        .axis                    = axis,
        .frame                   = frame,
        .axis_source             = axis_source,
        .axis_stop               = axis_stop,
        .axis_discrete           = axis_discrete,
        .axis_value120           = axis_value120,
        .axis_relative_direction = axis_relative_direction,
    };
};

class XdgWmBaseHandler {
    static void ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial);

public:
    static constexpr const xdg_wm_base_listener listener{
        .ping = ping,
    };
};

class XdgToplevelHandler {
    static void configure(
        void*                                 data,
        [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
        [[maybe_unused]] int32_t              width,
        [[maybe_unused]] int32_t              height,
        [[maybe_unused]] struct wl_array*     states
    );

    static void
    close(void* data, [[maybe_unused]] struct xdg_toplevel* xdg_toplevel);

    static void configure_bounds(
        void*                                 data,
        [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
        [[maybe_unused]] int32_t              width,
        [[maybe_unused]] int32_t              height
    );

    static void wm_capabilities(
        void*                                 data,
        [[maybe_unused]] struct xdg_toplevel* xdg_toplevel,
        [[maybe_unused]] struct wl_array*     capabilities
    );

public:
    static constexpr const xdg_toplevel_listener listener{
        .configure        = configure,
        .close            = close,
        .configure_bounds = configure_bounds,
        .wm_capabilities  = wm_capabilities,
    };
};

class SurfaceHandler {
    static void done(void* data, wl_callback* wl_callback, uint32_t time);

public:
    constexpr static const wl_callback_listener listener{
        .done = done,
    };
};

class XdgSurfaceHandler {
    static void
    configure(void* data, xdg_surface* xdg_surface, uint32_t serial);

public:
    static constexpr const xdg_surface_listener listener{
        .configure = configure,
    };
};

class SeatHandler {
    static void wl_seat_handle_capabilities(
        void*    data,
        wl_seat* seat,
        uint32_t capabilities
    );

    static void wl_seat_name(
        void*                     data,
        [[maybe_unused]] wl_seat* wl_seat,
        const char*               name
    );

public:
    static constexpr const wl_seat_listener listener{
        .capabilities = wl_seat_handle_capabilities,
        .name         = wl_seat_name,
    };
};

class RegistryHandler {
    static void global(
        void*        data,
        wl_registry* registry,
        uint32_t     name,
        const char*  interface,
        uint32_t     version
    );

    static void remove(void* data, wl_registry* registry, uint32_t name);

public:
    static constexpr const wl_registry_listener listener{
        .global        = global,
        .global_remove = remove,
    };
};
