load("//rules:rg_cc.bzl", "rg_cc_library")

rg_cc_library(
    name = "application",
    hdrs = [
        "application.hpp",
        "input.hpp",
    ],
    srcs = [
        "application.cpp",
        "input.cpp",
        "detail/backends.cpp",
        "detail/backends.hpp",
        "detail/cocoa.cpp",
        "detail/cocoa.hpp",
        "detail/dwm.cpp",
        "detail/dwm.hpp",
        "detail/wayland.cpp",
        "detail/wayland.hpp",
        "detail/wayland/wl_include.hpp",
        "detail/wayland/wl_keyboard.cpp",
        "detail/wayland/wl_pointer.cpp",
        "detail/wayland/wl_registry.cpp",
        "detail/wayland/wl_seat.cpp",
        "detail/wayland/wl_surface.cpp",
        "detail/wayland/xdg_surface.cpp",
        "detail/wayland/xdg_toplevel.cpp",
        "detail/wayland/xdg_wm_base.cpp",
    ],
    deps = [
        "//raygame/core",
        "//raygame/core/drawing",
        "//third_party/wayland",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.hpp",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
