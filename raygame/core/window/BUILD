load("//rules:rg_cc_singlefile.bzl", "rg_cc_library")
COCOA_DEPS = []

DWM_DEPS = []

WAYLAND_DEPS = [
    "//raygame/core:logger",
    "//raygame/core/drawing:colour",
    "//raygame/core/math:random",
    "//third_party/wayland",
    "//third_party/system/xkbcommon"
]

X11_DEPS = [
    "//third_party/system/x11",
]

rg_cc_library(
    name = "window",
    hdrs = ["window.h"],
    srcs = [
        "detail/cocoa.cpp",
        "detail/cocoa.h",
        "detail/dwm.cpp",
        "detail/dwm.h",
        "detail/temple.cpp",
        "detail/temple.h",
        "detail/wayland.cpp",
        "detail/wayland.h",
        "detail/x11.cpp",
        "detail/x11.h",
        "window.cpp",
    ],
    deps = [
        "//raygame/core:config",
        "//raygame/core/math:vector",
        "//raygame/core/drawing:image",
    ],
    implementation_deps = [] + select({
        "//rules/gui:cocoa":    COCOA_DEPS,
        "//rules/gui:dwm":      DWM_DEPS,
        "//rules/gui:wayland":  WAYLAND_DEPS,
        "//rules/gui:x11":      X11_DEPS,
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
