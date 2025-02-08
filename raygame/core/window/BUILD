load("//rules:rg_cc_singlefile.bzl", "rg_cc_library")
rg_cc_library(
    name = "window",
    hdrs = ["window.h"],
    srcs = [
        "window.cpp",
        "detail/backends.h",
        "detail/backends.cpp",
        "detail/cocoa.h",
        "detail/dwm.h",
        "detail/temple.h",
        "detail/wayland.h",
        "detail/x11.h",
        "detail/cocoa.cpp",
        "detail/dwm.cpp",
        "detail/temple.cpp",
        "detail/wayland.cpp",
        "detail/wayland/wl_keyboard.cpp",
        "detail/wayland/wl_pointer.cpp",
        "detail/wayland/wl_registry.cpp",
        "detail/wayland/wl_seat.cpp",
        "detail/wayland/wl_surface.cpp",
        "detail/wayland/xdg_surface.cpp",
        "detail/wayland/xdg_toplevel.cpp",
        "detail/wayland/xdg_wm_base.cpp",
        "detail/x11.cpp",
    ],
    deps = [
        "//raygame/core:config",
        "//raygame/core/math:vector",
        "//raygame/core/drawing:image",
    ],
    implementation_deps = [
    ] + select({
        "//rules/os:android":   [],
        "//rules/os:bsd":       [],
        "//rules/os:linux":     [
            "//raygame/core:logger",
            "//raygame/core/drawing:colour",
            "//raygame/core/math:random",
            "//raygame/core/math:ring_average",
            "//third_party/wayland",
            "//third_party/system/xkbcommon",
            "//third_party/system/x11",
        ],
        "//rules/os:mac":       [],
        "//rules/os:qnx":       [],
        "//rules/os:windows":   [],
        "//conditions:default": [],
    }),
    visibility = [ "//visibility:public" ],
)

filegroup(
    name = "doxyfiles",
    srcs = glob([
            "**/*.h",
            "**/*.dox",
        ],
        allow_empty = True,
    ),
    visibility = ["//visibility:public"],
)
