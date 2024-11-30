cc_library(
    name = "wayland-protocols",
    hdrs = [
        "wayland-client-protocol.h",
        "xdg-shell-client-protocol.h",
    ],
    srcs = [
        "wayland-protocol.c",
        "xdg-shell-protocol.c",
    ],
    includes = ["."],
    conlyopts = ["-w"], # Disable warnings as this is generated external code
    deps = [
        "//subprojects/host:libwayland-client",
        "//subprojects/host:libxkbcommon",
    ],
    visibility = ["//visibility:public"],
)

genrule(
    name = "wayland-header",
    srcs = [":wayland-xml"],
    outs = ["wayland-client-protocol.h"],
    cmd = "wayland-scanner client-header $< $@",
)

genrule(
    name = "wayland-source",
    srcs = [":wayland-xml"],
    outs = ["wayland-protocol.c"],
    cmd = "wayland-scanner public-code $< $@",
)

genrule(
    name = "xdg-shell-header",
    srcs = [":xdg-shell-xml"],
    outs = ["xdg-shell-client-protocol.h"],
    cmd = "wayland-scanner client-header $< $@",
)

genrule(
    name = "xdg-shell-source",
    srcs = [":xdg-shell-xml"],
    outs = ["xdg-shell-protocol.c"],
    cmd = "wayland-scanner public-code $< $@",
)

filegroup(
    name = "wayland-xml",
    srcs = ["wayland.xml"],
)

filegroup(
    name = "xdg-shell-xml",
    srcs = ["xdg-shell.xml"],
)
