cc_library(
    name = "detail",
    hdrs = ["wayland.h"],
    srcs = ["wayland.cpp"],
    deps = [":wayland-library"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "wayland-library",
    hdrs = [
        ":wayland-header",
        ":xdg-shell-header",
    ],
    srcs = [
        ":wayland-source",
        ":xdg-shell-source",
    ],
    deps = [
        "@usr//:libwayland-client",
    ],
)

genrule(
    name = "wayland-header",
    srcs = ["//subprojects/wayland-headers:wayland-protocol"],
    outs = ["wayland-client-protocol.h"],
    cmd = "wayland-scanner client-header $< $@",
)

genrule(
    name = "wayland-source",
    srcs = ["//subprojects/wayland-headers:wayland-protocol"],
    outs = ["wayland-protocol.c"],
    cmd = "wayland-scanner public-code $< $@",
)

genrule(
    name = "xdg-shell-header",
    srcs = ["//subprojects/wayland-headers:xdg-shell-protocol"],
    outs = ["xdg-shell-client-protocol.h"],
    cmd = "wayland-scanner client-header $< $@",
)

genrule(
    name = "xdg-shell-source",
    srcs = ["//subprojects/wayland-headers:xdg-shell-protocol"],
    outs = ["xdg-shell-protocol.c"],
    cmd = "wayland-scanner public-code $< $@",
)
