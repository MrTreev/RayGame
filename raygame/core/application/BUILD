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
    ] + select({
        "//rules/gui:cocoa": [
            "detail/cocoa.cpp",
            "detail/cocoa.hpp",
        ],
        "//rules/gui:dwm": [
            "detail/dwm.cpp",
            "detail/dwm.hpp",
        ],
        "//rules/gui:wayland": [
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
    }),
    deps = [
        "//raygame/core",
        "//raygame/core/drawing",
    ] + select({
        "//rules/gui:wayland": [
            "//third_party/wayland"
        ],
    }),
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
