filegroup(
    name = "wayland_sources",
    srcs = [
        "wayland/pixelbuffer.cpp",
        "wayland/region.cpp",
        "wayland/surface.cpp",
        "wayland/window.cpp",
    ],
    visibility = ["//visibility:private"],
)

filegroup(
    name = "wayland_headers",
    srcs = [
        "wayland/pixelbuffer.h",
        "wayland/region.h",
        "wayland/surface.h",
        "wayland/window.h",
    ],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "windowimpl",
    srcs = select({
        "@platforms//os:linux": [ ":wayland_sources" ],
    }),
    hdrs = select({
        "@platforms//os:linux": [ ":wayland_headers" ],
    }),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "doxygen_files",
    srcs = glob([
        "**/*.h",
        "**/*.inl",
        "**/*.dox",
    ]),
    visibility = [ "//visibility:public" ],
)
